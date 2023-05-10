#pragma once

#include "CoreMinimal.h"
#include "HUD/IntroductionBlock.h"
#include "IntroductionBlockWithPurchase.generated.h"

class ACombatInterfaceHUD;
class UButton;
class UTextBlock;
class UAttributeBlock;
class UScrollBox;

UCLASS()
class BROTATOCOPY_API UIntroductionBlockWithPurchase : public UIntroductionBlock
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct();

	UFUNCTION()
	void Purchase();

	void SetParent(UUserWidget* p) { Parent = p; }
	void SetIndex(int Index) { SlotIndex = Index; }

	void SetCost(int Cost);

private:
	UPROPERTY(meta = (BindWidget))
	UButton* PurchaseButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PurchaseCostText;

	UUserWidget* Parent; // ShopWidget or StrengthenWidget

	int PurchaseCost{ 0 };
	int SlotIndex;
};
