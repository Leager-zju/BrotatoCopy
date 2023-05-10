#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Commons/ItemInfo.h"
#include "Buttons/ItemButton.h"
#include "SelectionWidget.generated.h"

class AStarterHUD;
class UItemButton;
class UMyGameInstance;
class UTextBlock;
class UWrapBox;

UCLASS()
class BROTATOCOPY_API USelectionWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();

	void AddChildToShowBox(UWidget* Widget);
	void AddChildToShowBox(UWidget* Widget1, UWidget* Widget2);

	// Press ESC / Clock Button
	void BackToCharacterSelection();
	void EnterWeaponSelection();
	void BackToWeaponSelection();
	void EnterDifficultySelection();

	template<EButtonType ButtonType>
	void FillSelectBox(TArray<UClass*>& Informations, TSubclassOf<UItemButton> ButtonClass, EType ItemType);

public:
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Title;

	UPROPERTY(meta = (BindWidget))
	UWrapBox* ShowBox;

	UPROPERTY(meta = (BindWidget))
	UWrapBox* SelectBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UItemButton> SelectButtonClass;

	AStarterHUD* StarterHUD;

	UMyGameInstance* MyGameInstance;
};

