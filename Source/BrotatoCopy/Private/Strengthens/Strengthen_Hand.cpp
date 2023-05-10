#include "Strengthens/Strengthen_Hand.h"

AStrengthen_Hand::AStrengthen_Hand()
{
	StrengthenInfo.Name = FText::FromString(TEXT("手"));
	StrengthenInfo.Introduction = FText::FromString(TEXT("+1 收获"));
	StrengthenInfo.ItemClass = StaticClass();
}

void AStrengthen_Hand::BePurchasedBy(ACharacter_Base* Character)
{
	Character->GetMainAttribute().Acquisition += 1;
}
