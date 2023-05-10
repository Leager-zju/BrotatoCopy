#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "CombatGameMode.generated.h"
UCLASS()
class BROTATOCOPY_API ACombatGameMode : public AGameMode
{
	GENERATED_BODY()
	
public:
	void ChangeInputMode(bool IsCombat);
};
