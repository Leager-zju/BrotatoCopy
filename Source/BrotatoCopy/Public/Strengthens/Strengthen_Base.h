#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Characters/Character_Base.h"
#include "Commons/ItemInfo.h"
#include "Strengthen_Base.generated.h"

UCLASS()
class BROTATOCOPY_API AStrengthen_Base : public AActor
{
	GENERATED_BODY()
	
public:	
	AStrengthen_Base();
	virtual void BePurchasedBy(ACharacter_Base* Character) {}
	FItemInfo& GetInfo() { return StrengthenInfo; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;

protected:
	UPROPERTY(EditDefaultsOnly)
	FItemInfo StrengthenInfo {};
};
