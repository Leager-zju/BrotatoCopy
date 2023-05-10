#include "Props/Prop_Base.h"

AProp_Base::AProp_Base()
{
	PrimaryActorTick.bCanEverTick = false;
	PropInfo.ItemType = EType::Prop;
}

void AProp_Base::BeginPlay()
{
	Super::BeginPlay();
}

void AProp_Base::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

