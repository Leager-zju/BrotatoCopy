#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "MenuLevel.generated.h"

UCLASS()
class BROTATOCOPY_API AMenuLevel : public ALevelScriptActor
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay();
};
