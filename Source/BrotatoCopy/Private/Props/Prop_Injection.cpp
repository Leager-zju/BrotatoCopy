#include "Props/Prop_Injection.h"

AProp_Injection::AProp_Injection()
{
	PropInfo.Name = FText::FromString(TEXT("注射剂"));
	PropInfo.Introduction = FText::FromString(TEXT("+7%伤害\n-3最大生命值"));
	PropInfo.ItemClass = StaticClass();
	PropInfo.ItemType = EType::Prop;
	PropInfo.Rarity = ERarity::White;
}

void AProp_Injection::BePurchasedBy(ACharacter_Base* Character, int Cost)
{
	Character->GetMainAttribute().DamageRate += 7;
	Character->GetMainAttribute().MaxHealth -= 3;
	Character->BuyProp(GetPropInfo(), Cost);
}
