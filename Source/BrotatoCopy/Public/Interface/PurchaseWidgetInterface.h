#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PurchaseWidgetInterface.generated.h"

UINTERFACE(MinimalAPI)
class UPurchaseWidgetInterface : public UInterface
{
	GENERATED_BODY()
};

class BROTATOCOPY_API IPurchaseWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void ItemGetPurchaseAtIndex(int Index) = 0;
};
