#include "Weapons/Weapon_Base.h"

#include "Characters/Character_Base.h"
#include "Commons/CharacterAttribute.h"
#include "Commons/WeaponAttribute.h"
#include "Enemies/Enemy_Base.h"
#include "Weapons/Bullet_Base.h"

#include "Components/ArrowComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "PaperSpriteComponent.h"

AWeapon_Base::AWeapon_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	Arrow = CreateDefaultSubobject<UArrowComponent>(TEXT("Arrow"));
	Arrow->SetupAttachment(GetRootComponent());

	// WorldDynamic ÀàÐÍ
	GetRenderComponent()->SetCollisionObjectType(ECC_WorldDynamic);
	GetRenderComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetRenderComponent()->SetMobility(EComponentMobility::Movable);

	ActorsToIgnore.Add(this);

	WeaponInfo.ItemType = EType::Weapon;
}

void AWeapon_Base::SetPlayer(ACharacter_Base* p)
{
	ActorsToIgnore.Add(Cast<AActor>(p));
	Player = p;
}

void AWeapon_Base::Attack(FCharacterMainAttribute& CharacterAttribute)
{
	if (auto World = GetWorld()) {
		if (auto Bullet = World->SpawnActor<ABullet_Base>(BulletClass, Arrow->GetComponentTransform())) {
			bCanAttack = false;
			float BulletDamage = WeaponAttribute.CalculateDamage(CharacterAttribute);
			float CriticalRate = WeaponAttribute.CalculateCriticalRate(CharacterAttribute);
			float Random = FMath::RandRange(1, 100);
			if (Random <= CriticalRate) {
				BulletDamage *= WeaponAttribute.CriticalMutiplier;
			}
			Bullet->SetDamage(BulletDamage);
			Bullet->SetInstigator(Player);
			Bullet->SetOwner(this);
			Bullet->SetLifeSpan(WeaponAttribute.CalculateAttackRange(CharacterAttribute) / Bullet->GetSpeed());
			GetWorldTimerManager().SetTimer(AttackTimer, this, &AWeapon_Base::AttackTimeOut, AttackInterval);
		}
	}
}

bool AWeapon_Base::CanAttack(AActor*& Target, FCharacterMainAttribute& CharacterAttribute)
{
	if (!bCanAttack) return false;

	TArray<AEnemy_Base*> Enemies;
	double min_dis = WeaponAttribute.CalculateAttackRange(CharacterAttribute);
	AttackTarget = nullptr;

	TArray<FHitResult> OutHit;
	UKismetSystemLibrary::SphereTraceMulti(
		GetWorld(),
		GetActorLocation(),
		GetActorLocation(),
		min_dis,
		ETraceTypeQuery::TraceTypeQuery1,
		false,
		ActorsToIgnore,
		EDrawDebugTrace::None,
		OutHit,
		true);

	for (auto HitResult : OutHit) {
		if (HitResult.GetActor()) {
			AEnemy_Base* Enemy = Cast<AEnemy_Base>(HitResult.GetActor());
			if (Enemy) {
				Enemies.Add(Enemy);
			}
		}
	}

	for (auto Enemy : Enemies) {
		double dis = (Enemy->GetActorLocation() - GetActorLocation()).Size();
		if (dis < min_dis) {
			min_dis = dis;
			AttackTarget = Enemy;
		}
	}

	Target = AttackTarget;
	return AttackTarget != nullptr;
}

FItemInfo& AWeapon_Base::GetInfo(ERarity Rarity)
{
	switch (Rarity)
	{
	case ERarity::White:
		return GetInfoWithWhiteRarity();
	case ERarity::Blue:
		return GetInfoWithBlueRarity();
	case ERarity::Purple:
		return GetInfoWithPurpleRarity();
	case ERarity::Red:
		return GetInfoWithRedRarity();
	default:
		return WeaponInfo;
	}
}

FItemInfo& AWeapon_Base::GetInfoWithWhiteRarity()
{
	return WeaponInfo.WithName(WeaponName + TEXT("I")).WithRarity(ERarity::White);
}

FItemInfo& AWeapon_Base::GetInfoWithBlueRarity()
{
	return WeaponInfo.WithName(WeaponName + TEXT("II")).WithRarity(ERarity::Blue);
}

FItemInfo& AWeapon_Base::GetInfoWithPurpleRarity()
{
	return WeaponInfo.WithName(WeaponName + TEXT("III")).WithRarity(ERarity::Purple);
}

FItemInfo& AWeapon_Base::GetInfoWithRedRarity()
{
	return WeaponInfo.WithName(WeaponName + TEXT("IV")).WithRarity(ERarity::Red);
}

void AWeapon_Base::BeginPlay()
{
	Super::BeginPlay();
}

void AWeapon_Base::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);
}