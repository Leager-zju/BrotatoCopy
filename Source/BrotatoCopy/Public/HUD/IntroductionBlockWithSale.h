#pragma once

#include "CoreMinimal.h"
#include "HUD/IntroductionBlock.h"
#include "IntroductionBlockWithSale.generated.h"

class ACharacter_Base;
class UButton;
class UShopWidget;
class UTextBlock;

UCLASS()
class BROTATOCOPY_API UIntroductionBlockWithSale : public UIntroductionBlock
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();
	void SetSalePrice(int Price);
	void SetSlotIndex(int Index) { SlotIndex = Index; }

	UFUNCTION()
	void Composite();
 
	UFUNCTION()
	void Sale();

	UFUNCTION()
	void Cancel();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* CompositeButton;

	UPROPERTY(meta = (BindWidget))
	UButton* SaleButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* PriceText;

	UPROPERTY(meta = (BindWidget))
	UButton* CancelButton;

	int SalePrice{0};
	int SlotIndex{0};
};
