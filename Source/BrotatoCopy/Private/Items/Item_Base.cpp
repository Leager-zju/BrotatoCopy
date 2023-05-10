#include "Items/Item_Base.h"

#include "Characters/Character_Base.h"

#include "AIController.h"
#include "AITypes.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "PaperFlipBookComponent.h"
#include "PaperSpriteComponent.h"

AItem_Base::AItem_Base()
{
	PrimaryActorTick.bCanEverTick = true;
	// WorldDynamic ÀàÐÍ
	GetCapsuleComponent()->SetCollisionObjectType(ECC_WorldDynamic);
	GetCapsuleComponent()->SetCollisionResponseToAllChannels(ECR_Block);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Visibility, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Pawn, ECR_Ignore);

	GetCapsuleComponent()->SetCapsuleHalfHeight(500);
	GetCapsuleComponent()->SetCapsuleRadius(500);

	GetSprite()->SetRelativeRotation(FRotator(0, 0, 90));

	GetCharacterMovement()->MaxWalkSpeed = 2000;

	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;
}

void AItem_Base::BeginPlay()
{
	Super::BeginPlay();
	ItemController = Cast<AAIController>(GetController());
}

void AItem_Base::MoveTo(AActor* Target)
{
	FAIMoveRequest Request;
	Request.SetGoalLocation(Target->GetActorLocation());
	Request.SetAcceptanceRadius(50);
	ItemController->MoveTo(Request);
}

void AItem_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (PickupActor && ItemController) {
		MoveTo(PickupActor);
	}
}

