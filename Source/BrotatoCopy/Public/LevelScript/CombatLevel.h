#pragma once

#include "CoreMinimal.h"
#include "Engine/LevelScriptActor.h"
#include "CombatLevel.generated.h"

class ACharacter_Base;
class ACombatGameMode;
class ACombatInterfaceHUD;
class UMyGameInstance;

UCLASS()
class BROTATOCOPY_API ACombatLevel : public ALevelScriptActor
{
	GENERATED_BODY()
public:
	virtual void BeginPlay();
	void BeginNewRound();
	void RoundOver();
	void DestoryAllEnemy();
	void PickupAllAssets();

private:
	UPROPERTY(VisibleAnywhere)
	ACombatGameMode* CombatGameMode;

	UPROPERTY(VisibleAnywhere)
	ACombatInterfaceHUD* CombatHUD;

	UPROPERTY(VisibleAnywhere)
	UMyGameInstance* MyGameIns;

	UPROPERTY(VisibleAnywhere)
	ACharacter_Base* CurCharacter;

	UPROPERTY(VisibleAnywhere)
	int CurRound {0};	// 当前波数
	
	UPROPERTY(VisibleAnywhere)
	int CountDown {5};
	
	FTimerHandle RoundTimer;	// 敌袭倒计时计时器

	FTimerHandle WaitTimer;		// 敌袭结束后稍等一会
};
