#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Commons/ItemInfo.h"
#include "ItemButton.generated.h"

class UButton;
class UImage;
class UIntroductionBlock;
class UMyGameInstance;
class URecordBlock;
class USelectionWidget;
class UShopWidget;

UENUM(BlueprintType)
enum class EButtonType : uint8 {
	CharacterSelect,
	WeaponSelect,
	CharacterComment,
	WeaponComment,
	PropComment
};

UCLASS()
class BROTATOCOPY_API UItemButton : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct();

	UFUNCTION()
	void OnHovered();

	UFUNCTION()
	void OnClicked();

	UFUNCTION()
	void OnUnhovered();

	void SetItemInfo(FItemInfo& Info);
	FItemInfo& GetItemInfo() { return ItemInfo; }
	void SetType(EButtonType Type) { ButtonType = Type; }
	int GetSlotIndex() { return SlotIndex; }
	void SetSlotIndex(int Index) { SlotIndex = Index; }
	
protected:
	UPROPERTY(meta = (BindWidget))
	UButton* Button;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Img;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UIntroductionBlock> IntroductionBlockClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<URecordBlock> RecordBlockClass;

	UMyGameInstance* MyGameInstance;
	UIntroductionBlock* IntroductionBlock;
	URecordBlock* RecordBlock;
	FItemInfo ItemInfo;
	EButtonType ButtonType;

	int SlotIndex{0};
};
