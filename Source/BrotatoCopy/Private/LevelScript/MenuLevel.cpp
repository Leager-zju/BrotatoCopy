#include "LevelScript/MenuLevel.h"

#include "Kismet/GameplayStatics.h"

void AMenuLevel::BeginPlay()
{
	Super::BeginPlay();
	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			PC->SetShowMouseCursor(true);
		}
	}
}
