#pragma once

#include "CoreMinimal.h"
#include "ItemInfo.generated.h"

UENUM(BlueprintType)
enum class EType : uint8 {
	Character,
	Enemy,
	Weapon,
	Prop,
	Strengthen
};

UENUM(BlueprintType)
enum class ERarity : uint8 {
	White,
	Blue,
	Purple,
	Red
};

USTRUCT(BlueprintType)
struct FItemInfo {
	GENERATED_USTRUCT_BODY()

	UPROPERTY(EditAnywhere)
	struct FSlateBrush Img;

	UPROPERTY(EditAnywhere)
	FText Name;

	UPROPERTY(EditAnywhere)
	FText Introduction;

	UPROPERTY(EditAnywhere)
	UClass* ItemClass;
	
	UPROPERTY(EditAnywhere)
	EType ItemType;

	UPROPERTY(EditAnywhere)
	ERarity Rarity = ERarity::White;

	FItemInfo& WithName(const FString& str) {
		Name = FText::FromString(str);
		return *this;
	}
	
	FItemInfo& WithRarity(ERarity R) {
		Rarity = R;
		return *this;
	}
};