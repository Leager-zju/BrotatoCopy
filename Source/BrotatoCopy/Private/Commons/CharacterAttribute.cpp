#include "Commons/CharacterAttribute.h"

#include "Characters/Character_Base.h"

void FCharacterMainAttribute::SetOwner(ACharacter_Base* NewOwner)
{
	Owner = NewOwner;
}

float FCharacterMainAttribute::GetHealthPercent()
{
	return CurHealth / MaxHealth;
}

float FCharacterMainAttribute::GetExpPercent()
{
	return CurExp / ExpRequiredToLevelUp;
}

void FCharacterMainAttribute::IncreaseAssets(float Value)
{
	Assets += Value;
}

void FCharacterMainAttribute::IncreaseUnpicked(float Value)
{
	Unpicked += Value;
}

void FCharacterMainAttribute::IncreaseExp(float Value)
{
	CurExp += Value;
	while (CurExp >= ExpRequiredToLevelUp) {
		LevelUp();
	}
}

void FCharacterMainAttribute::LevelUp()
{
	Level++;
	CurHealth++;
	MaxHealth++;
	if (Owner) {
		Owner->LevelUp();
	}

	CurExp -= ExpRequiredToLevelUp;
	// TODO：修改升级所需最大经验
}

void FCharacterMainAttribute::ReceiveDamage(float Damage)
{
	CurHealth -= Damage;
	if (CurHealth < 0) {
		CurHealth = 0;
	}
}

bool FCharacterMainAttribute::Alive()
{
	return CurHealth > 0;
}
