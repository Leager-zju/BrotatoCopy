#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Interface/PurchaseWidgetInterface.h"
#include "ShopWidget.generated.h"

class ACharacter_Base;
class ACombatLevel;
struct FCharacterMainAttribute;
struct FCharacterSecondaryAttribute;
struct FPropInfo;
struct FWeaponInfo;
class UAttributeBlock;
class UButton;
class UIntroductionBlock;
class UIntroductionBlockWithSale;
class UItemButton;
class UMyGameInstance;
class UScrollBox;
class USizeBox;
class UTextBlock;

UCLASS()
class BROTATOCOPY_API UShopWidget : public UUserWidget, public IPurchaseWidgetInterface
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();
	void SetCurAsset(int Value);
	virtual void ItemGetPurchaseAtIndex(int Index);
	void SetRound(int Value);
	void SetRefreshCost(int Value);
	void SetFreeRefreshTime(int Value);
	void UpdateAttributeBox(FCharacterMainAttribute& MainAttr, FCharacterSecondaryAttribute& SecondaryAttr);
	void UpdateProps(TArray<FPropInfo>& PropsOwned);
	void UpdateWeapons(TArray<FWeaponInfo>& WeaponsOwned);
	void CreatePropCommentBlock(UItemButton* Button);
	void RemovePropCommentBlock();
	void CreateWeaponCommentBlock(UItemButton* Button);
	void RemoveWeaponCommentBlock();
	int GetRefreshCost() { return FreeRefreshTime ? 0 : RefreshCost; }

private:
	UFUNCTION()
	void Refresh();

	void CreateCommodityBlock(APlayerController* PC);

	UFUNCTION()
	void BeginNewRound();

	void SetUnaffordble();
private:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* ShopRound;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurAsset;

	UPROPERTY(meta = (BindWidget))
	UButton* RefreshButton;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* RefreshCostText;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* PropBox;

	UPROPERTY(meta = (BindWidget))
	UScrollBox* WeaponBox;

	UPROPERTY(meta = (BindWidget))
	USizeBox* AttributeBox;

	UPROPERTY(meta = (BindWidget))
	UButton* NextRound;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UIntroductionBlock> CommodityBlockClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemButton> ItemButtonClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UAttributeBlock> AttributeBlockClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UIntroductionBlock> PropCommentblockClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UIntroductionBlockWithSale> WeaponCommentblockClass;

	TArray<USizeBox*> CommodityBoxes;
	UAttributeBlock* AttributeBlock;
	UIntroductionBlock* PropCommentBlock;
	UIntroductionBlockWithSale* WeaponCommentBlock;
	ACombatLevel* CombatLevel;	// Call Begin New Round
	UMyGameInstance* MyGameIns;

	int RefreshCost{ 0 };
	int FreeRefreshTime{ 0 };	// 免费刷新次数
	int NumofCommodity;
};
