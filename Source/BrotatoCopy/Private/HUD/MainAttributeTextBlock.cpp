#include "HUD/MainAttributeTextBlock.h"

#include "Components/TextBlock.h"

void UMainAttributeTextBlock::UpdateAttr(const FCharacterMainAttribute& Attr)
{
	Level->SetText(TransformValueToFText(Attr.Level));
	MaxHealth->SetText(TransformValueToFText(Attr.MaxHealth));
	HealthRecovery->SetText(TransformValueToFText(Attr.HealthRecovery));
	HealthStealRate->SetText(TransformValueToFText(Attr.HealthStealRate));
	DamageRate->SetText(TransformValueToFText(Attr.DamageRate));
	MeleeDamage->SetText(TransformValueToFText(Attr.MeleeDamage));
	RangedDamage->SetText(TransformValueToFText(Attr.RangedDamage));
	ElementalDamage->SetText(TransformValueToFText(Attr.ElementalDamage));
	AttackSpeedRate->SetText(TransformValueToFText(Attr.AttackSpeedRate));
	CriticalRate->SetText(TransformValueToFText(Attr.CriticalRate));
	Engneering->SetText(TransformValueToFText(Attr.Engineering));
	AttackRange->SetText(TransformValueToFText(Attr.AttackRange));
	Armor->SetText(TransformValueToFText(Attr.Armor));
	DodgeRate->SetText(TransformValueToFText(Attr.DodgeRate));
	Speed->SetText(TransformValueToFText(Attr.Speed));
	Luck->SetText(TransformValueToFText(Attr.Luck));
	Acquisition->SetText(TransformValueToFText(Attr.Acquisition));
}
