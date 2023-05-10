#include "HUD/StarterHUD.h"

#include "GameMode/StarterGameMode.h"
#include "HUD/MenuWidget.h"
#include "HUD/SelectionWidget.h"

#include "Blueprint/UserWidget.h"
#include "Kismet/GameplayStatics.h"

void AStarterHUD::BeginPlay()
{
	Super::BeginPlay();

	if (auto World = GetWorld()){
		if (auto PC = World->GetFirstPlayerController()) {
			MenuWidget = CreateWidget<UMenuWidget>(PC, MenuWidgetClass);
			if (MenuWidget) {
				MenuWidget->AddToViewport();
			}
		}
		StarterGameMode = Cast<AStarterGameMode>(UGameplayStatics::GetGameMode(World));
	}
}

// only called by press ESC: Back from CharacterSelection
void AStarterHUD::BackToMenu()
{
	if (SelectionWidget && StarterState == EStarterState::CharacterSelect) {
		SelectionWidget->RemoveFromParent();
	}

	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			UE_LOG(LogTemp, Warning, TEXT("[Starter]: Back to Menu"));
			MenuWidget = CreateWidget<UMenuWidget>(PC, MenuWidgetClass);
			if (MenuWidget) {
				MenuWidget->AddToViewport();
			}
			if (StarterGameMode) {
				StarterGameMode->SetStarterState(EStarterState::Menu);
				StarterState = EStarterState::Menu;
			}
		}
	}
}

// only called by press ¿ªÊ¼: Enter from Menu
void AStarterHUD::EnterCharacterSelection()
{
	if (MenuWidget && StarterState == EStarterState::Menu) {
		MenuWidget->RemoveFromParent();
	}

	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			UE_LOG(LogTemp, Warning, TEXT("[Starter]: Enter Character Selection"));
			SelectionWidget = CreateWidget<USelectionWidget>(PC, SelectionWidgetClass);
			if (SelectionWidget) {
				SelectionWidget->AddToViewport();
			}
			if (StarterGameMode) {
				StarterGameMode->SetStarterState(EStarterState::CharacterSelect);
				StarterState = EStarterState::CharacterSelect;
			}
		}
	}
}

// only called by press ESC: Back from WeaponSelection
void AStarterHUD::BackToCharacterSelection()
{
	if (SelectionWidget && StarterState == EStarterState::WeaponSelect) {
		SelectionWidget->BackToCharacterSelection();
		StarterState = EStarterState::CharacterSelect;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("[Starter]: ERROR STATE %d"), StarterState);
	}
}

// only called by press CharacterSelectButton: Enter from CharacterSelection
void AStarterHUD::EnterWeaponSelection()
{
	if (SelectionWidget && StarterState == EStarterState::CharacterSelect) {
		SelectionWidget->EnterWeaponSelection();
		StarterState = EStarterState::WeaponSelect;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("[Starter]: ERROR STATE %d"), StarterState);
	}
}

// only called by press ESC: Back from DiffcultySelection
void AStarterHUD::BackToWeaponSelection()
{
	if (SelectionWidget && StarterState == EStarterState::DifficultySelect) {
		SelectionWidget->BackToWeaponSelection();
		StarterState = EStarterState::WeaponSelect;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("[Starter]: ERROR STATE %d"), StarterState);
	}
}

// only called by press WeaponSelectButton: Enter from WeaponSelection
void AStarterHUD::EnterDifficultySelection()
{
	if (SelectionWidget && StarterState == EStarterState::WeaponSelect) {
		SelectionWidget->EnterDifficultySelection();
		StarterState = EStarterState::DifficultySelect;
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("[Starter]: ERROR STATE %d"), StarterState);
	}
}
