#pragma once

#include "CoreMinimal.h"
#include "Items/Item_Base.h"
#include "Item_Drop.generated.h"

UCLASS()
class BROTATOCOPY_API AItem_Drop : public AItem_Base
{
	GENERATED_BODY()

public:
	AItem_Drop();
	float GetAssets() { return Assets; }
	void SetAssets(float Value) { Assets = Value; }
	float GetExp() { return Exp; }
	void SetExp(float Value) { Exp = Value; }

private:
	UPROPERTY(EditDefaultsOnly)
	float Assets;

	UPROPERTY(EditDefaultsOnly)
	float Exp;
};
