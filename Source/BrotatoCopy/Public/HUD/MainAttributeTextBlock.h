#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Commons/CharacterAttribute.h"
#include "MainAttributeTextBlock.generated.h"

class UTextBlock;

UCLASS()
class BROTATOCOPY_API UMainAttributeTextBlock : public UUserWidget
{
	GENERATED_BODY()

public:
	FText TransformValueToFText(int Value) { return FText::FromString(FString::FromInt(Value)); }
	void UpdateAttr(const FCharacterMainAttribute& Attr);

private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Level;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHealth;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthRecovery;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* HealthStealRate;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DamageRate;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MeleeDamage;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* RangedDamage;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ElementalDamage;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackSpeedRate;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* CriticalRate;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Engneering;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* AttackRange;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Armor;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* DodgeRate;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Speed;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Luck;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Acquisition;
};
