#include "Enemies/Enemy_Base.h"

#include "Characters/Character_Base.h"
#include "Commons/EnemyAttribute.h"
#include "Items/Item_Drop.h"

#include "AIController.h"
#include "AITypes.h"
#include "Components/CapsuleComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PaperFlipBookComponent.h"
#include "PaperFlipBook.h"

AEnemy_Base::AEnemy_Base()
{
	PrimaryActorTick.bCanEverTick = true;

	// Pawn ÀàÐÍ
	GetCapsuleComponent()->SetCollisionObjectType(ECC_Pawn);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

	bUseControllerRotationYaw = false;
}

void AEnemy_Base::BeginPlay()
{
	Super::BeginPlay();

	EnemyController = Cast<AAIController>(GetController());

	auto World = GetWorld();
	if (World) {
		AttackTarget = Cast<ACharacter_Base>(UGameplayStatics::GetActorOfClass(World, AttackTargetClass));
	}

	if (Walk) {
		GetSprite()->SetFlipbook(Walk);
	}
}

void AEnemy_Base::Tick(float DeltaSeconds)
{
	Super::Tick(DeltaSeconds);

	if (CanAttack()) {
		Attack();
	}
	else if (EnemyAttribute.Alive()){
		MoveTo(AttackTarget);
	}
}

float AEnemy_Base::TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	if (!EnemyAttribute.Alive()) {
		return 0;
	}

	UE_LOG(LogTemp, Warning, TEXT("[Enemy]: %s Take Damage %.f"), *GetName(), Damage);
	EnemyAttribute.ReceiveDamage(Damage);
	if (!EnemyAttribute.Alive()) {
		Die();
	}
	return Damage;
}

bool AEnemy_Base::CanAttack()
{
	if (!bCanAttack || AttackTarget == nullptr) return false;

	FVector CharacterLocation = AttackTarget->GetActorLocation();
	FVector EnemyLocation = GetActorLocation();
	return (CharacterLocation - EnemyLocation).Size() <= EnemyAttribute.AttackRange;
}

void AEnemy_Base::Attack()
{
	bCanAttack = false;
	UGameplayStatics::ApplyDamage(AttackTarget, EnemyAttribute.Damage, GetController(), this, UDamageType::StaticClass());
	GetWorldTimerManager().SetTimer(AttackTimer, this, &AEnemy_Base::AttackTimeOut, AttackInterval);
}

void AEnemy_Base::MoveTo(AActor* Target)
{
	if (EnemyController && Target) {
		FAIMoveRequest MoveRequest;
		MoveRequest.SetGoalLocation(Target->GetActorLocation());
		MoveRequest.SetAcceptanceRadius(EnemyAttribute.AttackRange);

		if ((Target->GetActorLocation() - GetActorLocation()).X < 0) {
			GetSprite()->SetRelativeRotation(FRotator(180, 0, -90));
		}
		else {
			GetSprite()->SetRelativeRotation(FRotator(0, 0, -90));
		}
		EnemyController->MoveTo(MoveRequest);
	}
}

void AEnemy_Base::Die()
{
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	EnemyController->StopMovement();
	
	auto World = GetWorld();
	if (World) {
		AItem_Drop* Item = World->SpawnActor<AItem_Drop>(DropItemClass, GetActorTransform());
		if (Item) {
			Item->SpawnDefaultController();
			Item->SetAssets(EnemyAttribute.AssetsGenerated);
			Item->SetExp(EnemyAttribute.ExpGenerated);
		}
	}

	if (Dead) {
		GetSprite()->SetFlipbook(Dead);
		SetLifeSpan(Dead->GetNumFrames() / Dead->GetFramesPerSecond() - 0.3);
	}
}
