#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/Character_Base.h"
#include "Commons/ItemInfo.h"
#include "Prop_Base.generated.h"

UCLASS()
class BROTATOCOPY_API AProp_Base : public AActor
{
	GENERATED_BODY()
	
public:
	AProp_Base();
	virtual void BePurchasedBy(ACharacter_Base* Character, int Cost) {}
	FPropInfo GetPropInfo() { return FPropInfo(PropInfo.ItemClass, 1, PropInfo.Rarity); }
	FItemInfo& GetInfo() { return PropInfo; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	FItemInfo PropInfo {};
};
