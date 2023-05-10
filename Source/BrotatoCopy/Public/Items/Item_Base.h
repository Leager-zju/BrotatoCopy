#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Item_Base.generated.h"

class USphereComponent;
class AAIController;

UENUM(BlueprintType)
enum class EItemType : uint8 {
	NIL,
	Drop,
	NormalChest,
	RareChest
};

UCLASS()
class BROTATOCOPY_API AItem_Base : public APaperCharacter
{
	GENERATED_BODY()
	
public:	
	AItem_Base();
	void SetPickUpActor(AActor* Actor) { PickupActor = Actor; }
	EItemType GetType() { return Type; }

protected:
	virtual void BeginPlay() override;
	virtual void Tick(float DeltaTime) override;
	void MoveTo(AActor* Target);

protected:
	UPROPERTY(VisibleAnywhere)
	AAIController* ItemController;

	UPROPERTY(VisibleAnywhere)
	AActor* PickupActor { nullptr };

	EItemType Type = EItemType::NIL;
};
