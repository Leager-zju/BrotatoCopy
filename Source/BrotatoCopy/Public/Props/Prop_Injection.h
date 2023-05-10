#pragma once

#include "CoreMinimal.h"
#include "Props/Prop_Base.h"
#include "Prop_Injection.generated.h"

/**
 * 注射剂：+7% 伤害，-3 最大生命值
 */
UCLASS()
class BROTATOCOPY_API AProp_Injection : public AProp_Base
{
	GENERATED_BODY()
public:
	AProp_Injection();
	virtual void BePurchasedBy(ACharacter_Base* Character, int Cost) override;
};
