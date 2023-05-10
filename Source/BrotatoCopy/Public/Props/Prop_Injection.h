#pragma once

#include "CoreMinimal.h"
#include "Props/Prop_Base.h"
#include "Prop_Injection.generated.h"

/**
 * ע�����+7% �˺���-3 �������ֵ
 */
UCLASS()
class BROTATOCOPY_API AProp_Injection : public AProp_Base
{
	GENERATED_BODY()
public:
	AProp_Injection();
	virtual void BePurchasedBy(ACharacter_Base* Character, int Cost) override;
};
