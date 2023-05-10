#pragma once

#include "CoreMinimal.h"
#include "Strengthens/Strengthen_Base.h"
#include "Strengthen_Hand.generated.h"

UCLASS()
class BROTATOCOPY_API AStrengthen_Hand : public AStrengthen_Base
{
	GENERATED_BODY()
public:
	AStrengthen_Hand();
	virtual void BePurchasedBy(ACharacter_Base* Character);
};
