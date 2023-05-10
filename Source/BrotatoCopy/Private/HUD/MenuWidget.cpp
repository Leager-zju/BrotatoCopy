#include "HUD/MenuWidget.h"

#include "HUD/StarterHUD.h"

#include "Components/Button.h"
#include "Kismet/GameplayStatics.h"

void UMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	StartButton->OnClicked.AddDynamic(this, &UMenuWidget::StartButtonClicked);

	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			StarterHUD = Cast<AStarterHUD>(PC->GetHUD());
		}
	}
}

void UMenuWidget::StartButtonClicked()
{
	UE_LOG(LogTemp, Warning, TEXT("[Menu]: Start Button Be Clicked"));
	if (StarterHUD) {
		StarterHUD->EnterCharacterSelection();
	}
}

