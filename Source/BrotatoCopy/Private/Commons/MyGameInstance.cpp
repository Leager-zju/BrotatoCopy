#include "Commons/MyGameInstance.h"

UClass* UMyGameInstance::RandomWeaponPropClass()
{
	int RandomIndex = FMath::RandRange(0, WeaponsOwned.Num() + PropClasses.Num() - 1);
	return RandomIndex < WeaponsOwned.Num() ? WeaponsOwned[RandomIndex] : PropClasses[RandomIndex - WeaponsOwned.Num()];
}

UClass* UMyGameInstance::RandomStrengthenClass()
{
	int RandomIndex = FMath::RandRange(0, StrengthenClasses.Num() - 1);
	return StrengthenClasses[RandomIndex];
}
