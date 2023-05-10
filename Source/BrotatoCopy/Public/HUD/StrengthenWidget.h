#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/PurchaseWidgetInterface.h"
#include "StrengthenWidget.generated.h"

class UWrapBox;
class UButton;
class UTextBlock;
class UIntroductionBlock;
class UMyGameInstance;
class ACombatInterfaceHUD;
class ACharacter_Base;

UCLASS()
class BROTATOCOPY_API UStrengthenWidget : public UUserWidget, public IPurchaseWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();
	void SetCurAsset(int Value);
	virtual void ItemGetPurchaseAtIndex(int Index);
	void SetRefreshCost(int Value);
	void SetHUD(ACombatInterfaceHUD* HUD) { CombatHUD = HUD; }

private:
	UFUNCTION()
	void Refresh();

	void CreateStrengthenBlock(APlayerController* PC);
	void SetUnaffordble();

private:
	UPROPERTY(meta = (BindWidget))
	UWrapBox* StrengthenBox;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurAsset;

	UPROPERTY(meta = (BindWidget))
	UButton* RefreshButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RefreshCostText;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UIntroductionBlock> StrengthenBlockClass;

	ACombatInterfaceHUD* CombatHUD;

	UMyGameInstance* MyGameIns;

	int RefreshCost{ 0 };
};