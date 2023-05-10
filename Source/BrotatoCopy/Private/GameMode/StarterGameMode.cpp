#include "GameMode/StarterGameMode.h"

#include "HUD/StarterHUD.h"

#include "Kismet/KismetSystemLibrary.h"

void AStarterGameMode::BeginPlay()
{
	Super::BeginPlay();
	if (InputComponent) {
		InputComponent->BindAction("Quit", IE_Pressed, this, &AStarterGameMode::Quit);
	}

	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			StarterHUD = Cast<AStarterHUD>(PC->GetHUD());
		}
	}
}

void AStarterGameMode::Quit()
{
	if (StarterHUD) {
		switch (StarterState)
		{
		case EStarterState::Menu:
			if (auto World = GetWorld()) {
				if (auto PC = World->GetFirstPlayerController()) {
					UKismetSystemLibrary::QuitGame(World, PC, EQuitPreference::Quit, true);
				}
			}
			break;
		case EStarterState::CharacterSelect:
			StarterHUD->BackToMenu();
			break;
		case EStarterState::WeaponSelect:
			StarterHUD->BackToCharacterSelection();
			break;
		case EStarterState::DifficultySelect:
			StarterHUD->BackToCharacterSelection();
		default:
			break;
		}
	}
}
