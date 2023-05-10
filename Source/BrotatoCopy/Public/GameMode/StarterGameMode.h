#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "Commons/StarterType.h"
#include "StarterGameMode.generated.h"

class AStarterHUD;

UCLASS()
class BROTATOCOPY_API AStarterGameMode : public AGameMode
{
	GENERATED_BODY()
public:
	void Quit();
	EStarterState GetStarterState() { return StarterState; }
	void SetStarterState(EStarterState NewState) { StarterState = NewState; }

protected:
	virtual void BeginPlay();

protected:
	UPROPERTY(VisibleAnywhere)
	EStarterState StarterState;

	UPROPERTY(VisibleAnywhere)
	AStarterHUD* StarterHUD;
};
