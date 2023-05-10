#include "Commons/WeaponAttribute.h"
#include "Commons/CharacterAttribute.h"

float FWeaponAttribute::CalculateAttackRange(const FCharacterMainAttribute& Attribute)
{
	float AttackRange = BasicAttackRange + Attribute.AttackRange;
	return FMath::Max(AttackRange, 1);
}

float FWeaponAttribute::CalculateDamage(const FCharacterMainAttribute& Attribute)
{
	float Damage = BasicDamage;
	Damage += MeleeMultiplier / 100 * Attribute.MeleeDamage;
	Damage += RangedMultiplier / 100 * Attribute.RangedDamage;
	Damage += ElementalMultiplier / 100 * Attribute.ElementalDamage;
	Damage += EngneerMultiplier / 100 * Attribute.Engineering;

	return FMath::Max(FMath::RoundToInt(Damage), 1);
}

float FWeaponAttribute::CalculateCriticalRate(const FCharacterMainAttribute& Attribute)
{
	return BasicCriticalRate + Attribute.CriticalRate;
}

