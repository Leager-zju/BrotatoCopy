#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "Commons/StarterType.h"
#include "StarterHUD.generated.h"

class UMenuWidget;
class USelectionWidget;
class UWidget;
class AStarterGameMode;

UCLASS()
class BROTATOCOPY_API AStarterHUD : public AHUD
{
	GENERATED_BODY()

public:
	virtual void BeginPlay();

	void BackToMenu();
	void EnterCharacterSelection();
	void BackToCharacterSelection();
	void EnterWeaponSelection();
	void BackToWeaponSelection();
	void EnterDifficultySelection();

	USelectionWidget* GetSelectionWidget() { return SelectionWidget; }

private:
	UPROPERTY(EditAnywhere)
	TSubclassOf<UMenuWidget> MenuWidgetClass;

	UPROPERTY(EditAnywhere)
	TSubclassOf<USelectionWidget> SelectionWidgetClass;

	AStarterGameMode* StarterGameMode;
	UMenuWidget* MenuWidget;
	USelectionWidget* SelectionWidget;
	EStarterState StarterState = EStarterState::Menu;
};
