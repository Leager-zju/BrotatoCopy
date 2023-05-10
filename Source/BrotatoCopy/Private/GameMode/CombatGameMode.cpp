#include "GameMode/CombatGameMode.h"

#include "Characters/Character_Base.h"
#include "Commons/MyGameInstance.h"
#include "HUD/CombatInterfaceHUD.h"

#include "Kismet/GameplayStatics.h"

void ACombatGameMode::ChangeInputMode(bool ShowMouse)
{
	UE_LOG(LogTemp, Warning, TEXT("Switch To Combat InputMode"));
	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {

			if (ShowMouse) {
				FInputModeUIOnly InputMode;
				InputMode.SetLockMouseToViewportBehavior(EMouseLockMode::LockAlways);
				PC->SetInputMode(InputMode);
			}
			else {
				FInputModeGameOnly InputMode;
				InputMode.SetConsumeCaptureMouseDown(true);
				PC->SetInputMode(InputMode);
			}

			PC->SetShowMouseCursor(ShowMouse);
		}
	}
}
