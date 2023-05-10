#include "Characters/Character_Base.h"

#include "Commons/MyGameInstance.h"
#include "Commons/ItemInfo.h"
#include "Commons/CharacterAttribute.h"
#include "HUD/CombatInterfaceHUD.h"
#include "Items/Item_Drop.h"
#include "LevelScript/CombatLevel.h"
#include "Weapons/Weapon_Base.h"

#include "GameFramework/SpringArmComponent.h"
#include "GameFramework/PawnMovementComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "PaperFlipBookComponent.h"



ACharacter_Base::ACharacter_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	// Pawn 类型，能与敌人模型产生重叠，并且要 Block Visibility 通道
	GetCapsuleComponent()->SetGenerateOverlapEvents(true);
	GetCapsuleComponent()->SetCollisionObjectType(ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	SpringArm->SetupAttachment(GetRootComponent());
	SpringArm->TargetArmLength = 2000;

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(SpringArm);

	MainAttribute.MaxHealth = 10;
	MainAttribute.CurHealth = 10;

	int MaxNumofWeapons = MainAttribute.MaxNumofWeapons;
	Weapons_Position.Init(nullptr, MaxNumofWeapons);
	WeaponsOwned.Init({}, MaxNumofWeapons);
	Weapons.Init(nullptr, MaxNumofWeapons);
	for (int i = 0; i < MaxNumofWeapons; i++) {
		FName WeaponName = *(FString("Weapon") + FString::FromInt(i));
		Weapons_Position[i] = CreateDefaultSubobject<USceneComponent>(WeaponName);
		Weapons_Position[i]->SetupAttachment(GetRootComponent());
		Weapons_Position[i]->SetRelativeRotation(FRotator(0, 0, 90));
	}

	PickUpSphere = CreateDefaultSubobject<USphereComponent>(TEXT("PickUp Sphere"));
	PickUpSphere->SetupAttachment(GetRootComponent());
	PickUpSphere->SetGenerateOverlapEvents(true);

	StreaminSphere = CreateDefaultSubobject<USphereComponent>(TEXT("Streamin Sphere"));
	StreaminSphere->SetupAttachment(GetRootComponent());
	StreaminSphere->SetGenerateOverlapEvents(true);
}

void ACharacter_Base::BeginPlay()
{
	Super::BeginPlay();

	PickUpSphere->OnComponentBeginOverlap.AddDynamic(this, &ACharacter_Base::Pickup);
	StreaminSphere->OnComponentBeginOverlap.AddDynamic(this, &ACharacter_Base::Streamin);
}

void ACharacter_Base::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
	if (GetMovementComponent()->Velocity.Size() && Run) {
		GetSprite()->SetFlipbook(Run);
	}
	else if (Idle) {
		GetSprite()->SetFlipbook(Idle);
	}
	TryAttack();
}

void ACharacter_Base::Initial()
{
	MainAttribute.SetOwner(this);
	PickUpSphere->SetSphereRadius(MainAttribute.PickUpRadius);
	StreaminSphere->SetSphereRadius(GetCapsuleComponent()->GetUnscaledCapsuleRadius());


	PC = Cast<APlayerController>(GetController());
	if (PC) {
		CombatHUD = Cast<ACombatInterfaceHUD>(PC->GetHUD());
	}

	MyGameIns = Cast<UMyGameInstance>(GetGameInstance());
	if (MyGameIns) {
		SetWeaponClassAtIndex(0, FWeaponInfo(MyGameIns->GetSelectedWeaponClass(), ERarity::White));
	}
}

void ACharacter_Base::BeginNewRound()
{
	UpdateCombatInterfaceWidget();
	ReEquipWeapon();
}

void ACharacter_Base::UpdateCombatInterfaceWidget()
{
	// 角色回复至最大生命值
	MainAttribute.CurHealth = MainAttribute.MaxHealth;
	if (CombatHUD) {
		CombatHUD->SetHealthBarPercent(1);
		CombatHUD->SetCurHealth(MainAttribute.CurHealth);
		CombatHUD->SetMaxHealth(MainAttribute.MaxHealth);
		CombatHUD->SetLevel(MainAttribute.Level);
		CombatHUD->SetExpBarPercent(MainAttribute.GetExpPercent());
		CombatHUD->SetCurAsset(MainAttribute.Assets);
		CombatHUD->SetUnpicked(MainAttribute.Unpicked);
	}
}

void ACharacter_Base::SetWeaponClassAtIndex(int index, const FWeaponInfo& NewWeapon)
{
	if (index < 0 || index >= MainAttribute.MaxNumofWeapons) {
		return;
	}
	WeaponsOwned[index] = NewWeapon;
}

float ACharacter_Base::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	UE_LOG(LogTemp, Warning, TEXT("%s Take Damage %.f"), *GetName(), Damage);
	float DodgeRate = MainAttribute.DodgeRate;
	float Random = FMath::RandRange(1, 100);
	if (Random <= DodgeRate) {
		Dodge();
		return 0;
	}

	MainAttribute.ReceiveDamage(Damage);

	if (CombatHUD) {
		CombatHUD->SetHealthBarPercent(MainAttribute.GetHealthPercent());
		CombatHUD->SetCurHealth(MainAttribute.CurHealth);
	}

	if (!MainAttribute.Alive()) {
		Die();
	}
	return Damage;
}

void ACharacter_Base::PickupAssets(float Assets, float Exp)
{
	if (MainAttribute.Unpicked--) {
		Assets++;
	}
	MainAttribute.IncreaseAssets(Assets);
	MainAttribute.IncreaseExp(Exp);
}

void ACharacter_Base::RecycleUnpickup(float Unpicked)
{
	MainAttribute.IncreaseUnpicked(Unpicked);
}

void ACharacter_Base::TakeCost(int Cost)
{
	MainAttribute.Assets -= Cost;
	if (CombatHUD) {
		CombatHUD->SetCurAsset(MainAttribute.Assets);
	}
}

void ACharacter_Base::BuyProp(const FPropInfo& NewProp, int Cost)
{
	if (PropClass2Index.Contains(NewProp.PropClass)) {
		int Index = PropClass2Index[NewProp.PropClass];
		PropsOwned[Index].Count++;
	}
	else {
		int Index = PropsOwned.Add(NewProp);
		PropClass2Index.Add(NewProp.PropClass, Index);
	}
	TakeCost(Cost);
	if (CombatHUD) {
		CombatHUD->UpdateProps(PropsOwned);
		CombatHUD->UpdateAttr(GetMainAttribute(), GetSecondaryAttribute());
	}
}

void ACharacter_Base::BuyWeapon(const FWeaponInfo& NewWeapon, int Cost)
{
	int i = 0, n = MainAttribute.MaxNumofWeapons;
	while (i < n) {
		if (WeaponsOwned[i].WeaponClass == nullptr) {
			SetWeaponClassAtIndex(i, NewWeapon);
			break;
		}
		i++;
	}

	// 如果武器满，则寻找是否能够合成
	if (i == n) {
		while (--i) {
			if (CompositeWeapon(i, WeaponsOwned[i]) != -1) {
				break;
			}
		}
	}
	TakeCost(Cost);
	if (CombatHUD) {
		CombatHUD->UpdateWeapons(WeaponsOwned);
		CombatHUD->UpdateAttr(GetMainAttribute(), GetSecondaryAttribute());
	}
}

// public
int ACharacter_Base::CompositeWeapon(int WeaponIndex)
{
	if (WeaponIndex < 0 || WeaponIndex >= MainAttribute.MaxNumofWeapons || WeaponsOwned[WeaponIndex].WeaponClass == nullptr) {
		UE_LOG(LogTemp, Warning, TEXT("INVALID INDEX %d"), WeaponIndex);
		return -1;
	}

	int res = CompositeWeapon(WeaponIndex, WeaponsOwned[WeaponIndex]);
	if (res != -1) {
		RemoveWeapon(res);
	}
	return res;
}

// private
int ACharacter_Base::CompositeWeapon(int WeaponIndex, const FWeaponInfo& Weapon)
{
	if (Weapon.Rarity == ERarity::Red) {
		UE_LOG(LogTemp, Warning, TEXT("Highest Rarity"));
		return -1;
	}
	for (int i = 0, n = MainAttribute.MaxNumofWeapons; i < n && WeaponsOwned[i].WeaponClass; i++) {
		if (i == WeaponIndex) continue;

		if (WeaponsOwned[i] == Weapon) {
			int protect = FMath::Min(i, WeaponIndex);
			int probation = FMath::Max(i, WeaponIndex);
			switch (WeaponsOwned[protect].Rarity) {
			case ERarity::White:
				WeaponsOwned[protect].Rarity = ERarity::Blue;
				break;
			case ERarity::Blue:
				WeaponsOwned[protect].Rarity = ERarity::Purple;
				break;
			case ERarity::Purple:
				WeaponsOwned[protect].Rarity = ERarity::Red;
				break;
			default:
				break;
			}
			UE_LOG(LogTemp, Warning, TEXT("Composite Success Between %d and %d"), protect, probation);
			return probation;
		}
	}
	UE_LOG(LogTemp, Warning, TEXT("Composite Failed"));
	return -1;
}

void ACharacter_Base::SellWeapon(int WeaponIndex, int Price)
{
	if (WeaponIndex < 0 || WeaponIndex >= MainAttribute.MaxNumofWeapons) return;
	RemoveWeapon(WeaponIndex);
	MainAttribute.Assets += Price;
	UE_LOG(LogTemp, Warning, TEXT("Sell Weapon And Get %d"), Price);
	if (CombatHUD) {
		CombatHUD->UpdateWeapons(WeaponsOwned);
		CombatHUD->SetCurAsset(MainAttribute.Assets);
	}
}

void ACharacter_Base::RemoveWeapon(int WeaponIndex)
{
	while (WeaponIndex < MainAttribute.MaxNumofWeapons - 1) {
		WeaponsOwned[WeaponIndex] = WeaponsOwned[WeaponIndex + 1];
		WeaponIndex++;
	}
	WeaponsOwned[WeaponIndex].WeaponClass = nullptr;
}

void ACharacter_Base::TryAttack()
{
	for (int i = 0, n = MainAttribute.MaxNumofWeapons; i < n; i++) {
		AActor* Target;
		if (Weapons[i] && Weapons[i]->CanAttack(Target, MainAttribute)) {
			Attack(i, Target);
		}
	}
}

/**
 * 重新生成 Weapon 并置于对应 WeaponPosition
 */ 
void ACharacter_Base::ReEquipWeapon()
{
	if (auto World = GetWorld()) {
		for (int i = 0, n = MainAttribute.MaxNumofWeapons; i < n && WeaponsOwned[i].WeaponClass; i++) {
			if (auto Weapon = World->SpawnActor<AWeapon_Base>(WeaponsOwned[i].WeaponClass, Weapons_Position[i]->GetComponentTransform())) {
				if (Weapons[i]) {
					Weapons[i]->Destroy();
				}
				
				Weapon->AttachToComponent(Weapons_Position[i], FAttachmentTransformRules(EAttachmentRule::SnapToTarget, true));
				Weapon->SetPlayer(this);
				Weapons[i] = Weapon;
			}
		}
	}
}

void ACharacter_Base::Attack(int Weapon_Index, AActor* Target)
{
	FVector StartLocation = Weapons_Position[Weapon_Index]->GetComponentLocation();
	FVector EndLocation = Target->GetActorLocation();
	FRotator LookAt = UKismetMathLibrary::FindLookAtRotation(StartLocation, EndLocation);
	LookAt.Roll = 90;
	Weapons_Position[Weapon_Index]->SetRelativeRotation(LookAt);
	Weapons[Weapon_Index]->Attack(MainAttribute);

}

void ACharacter_Base::Dodge()
{
	// TODO: 闪避
}

void ACharacter_Base::Die()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	if (Dead) {
		GetSprite()->SetFlipbook(Dead);
	}
	SetLifeSpan(0.8);
}

void ACharacter_Base::LevelUp()
{
	if (CombatHUD) {
		CombatHUD->SetLevel(MainAttribute.Level);
		CombatHUD->SetCurHealth(MainAttribute.CurHealth);
		CombatHUD->SetMaxHealth(MainAttribute.MaxHealth);
		CombatHUD->AddStrengthenTime();
	}
}

/**
 * Inputs
 */
void ACharacter_Base::SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent)
{
	PlayerInputComponent->BindAxis("MoveRight", this, &ACharacter_Base::MoveRight);
	PlayerInputComponent->BindAxis("MoveUp", this, &ACharacter_Base::MoveUp);
}

void ACharacter_Base::MoveRight(float Value)
{
	if (Controller && bInCombat) {
		AddMovementInput(GetActorForwardVector(), Value);
		// 左右移动时改变贴图
		if (Value > 0) {
			GetSprite()->SetRelativeRotation(FRotator(0, 0, -90));
		}
		else if (Value < 0) {
			GetSprite()->SetRelativeRotation(FRotator(180, 0, -90));
		}
	}
}

void ACharacter_Base::MoveUp(float Value)
{
	if (Controller && bInCombat) {
		AddMovementInput(GetActorRightVector(), Value);
	}
}

/**
 * Delegates
 */
void ACharacter_Base::Pickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (bInCombat && OtherActor) {
		if (AItem_Base* Item = Cast<AItem_Base>(OtherActor)) {
			Item->SetPickUpActor(this);
		}
	}
}

void ACharacter_Base::Streamin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OtherActor) {
		if (auto Item = Cast<AItem_Base>(OtherActor)) {
			switch (Item->GetType())
			{
			case EItemType::Drop:
				if (auto Drop = Cast<AItem_Drop>(Item)) {
					if (bInCombat) {
						PickupAssets(Drop->GetAssets(), Drop->GetExp());
					}
					else {
						RecycleUnpickup(Drop->GetAssets());
					}
					if (CombatHUD) {
						CombatHUD->SetExpBarPercent(MainAttribute.GetExpPercent());
						CombatHUD->SetCurAsset(MainAttribute.Assets);
					}
				}
				break;
			case EItemType::NormalChest:
				if (CombatHUD) {
					CombatHUD->AddChestCount(0);
				}
				break;
			case EItemType::RareChest:
				if (CombatHUD) {
					CombatHUD->AddChestCount(1);
				}
				break;
			default:
				break;
			}
			
			Item->Destroy();
		}
	}
}
