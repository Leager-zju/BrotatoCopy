#include "Strengthens/Strengthen_Base.h"

#include "Characters/Character_Base.h"

AStrengthen_Base::AStrengthen_Base()
{
 	PrimaryActorTick.bCanEverTick = false;
	StrengthenInfo.ItemType = EType::Strengthen;
}

void AStrengthen_Base::BeginPlay()
{
	Super::BeginPlay();
}

void AStrengthen_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

