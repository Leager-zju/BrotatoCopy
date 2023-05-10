#include "LevelScript/CombatLevel.h"

#include "Characters/Character_Base.h"
#include "Commons/MyGameInstance.h"
#include "Enemies/Enemy_Base.h"
#include "GameMode/CombatGameMode.h"
#include "HUD/CombatInterfaceHUD.h"
#include "Items/Item_Base.h"
#include "Weapons/Weapon_Base.h"

#include "GameFramework/DefaultPawn.h"
#include "Kismet/GameplayStatics.h"

void ACombatLevel::BeginPlay()
{
	Super::BeginPlay();

	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			CombatGameMode = Cast<ACombatGameMode>(UGameplayStatics::GetGameMode(World));
			CombatHUD = Cast<ACombatInterfaceHUD>(PC->GetHUD());
			MyGameIns = Cast<UMyGameInstance>(GetGameInstance());
			CurCharacter = Cast<ACharacter_Base>(UGameplayStatics::GetPlayerPawn(World, 0));

			if (CombatGameMode) {
				CombatGameMode->ChangeInputMode(false);
			}
			if (MyGameIns) {
				CombatGameMode->DefaultPawnClass = MyGameIns->GetSelectedCharacterClass();
			}
			if (CurCharacter) {
				CurCharacter->Initial();
				CurCharacter->SetCombatLevel(this);
			}
		}
	}

	BeginNewRound();
}

void ACombatLevel::BeginNewRound()
{
	GetWorldTimerManager().SetTimer(RoundTimer, this, &ACombatLevel::RoundOver, CountDown);
	CurRound++;
	if (CombatGameMode) {
		CombatGameMode->ChangeInputMode(false);
	}
	if (CombatHUD) {
		CombatHUD->SetRound(CurRound);
		CombatHUD->EnterCombat();
		CombatHUD->UpdateCountDown(CountDown);
	}
	if (CurCharacter) {
		CurCharacter->SetActorLocation(FVector(0, 0, 200));
		CurCharacter->EnableMove();
		CurCharacter->BeginNewRound();
	}
}

void ACombatLevel::RoundOver()
{
	if (CombatGameMode) {
		CombatGameMode->ChangeInputMode(true);
	}
	if (CurCharacter) {
		CurCharacter->DisableMove();
	}
	DestoryAllEnemy();
	PickupAllAssets();
	GetWorldTimerManager().SetTimer(WaitTimer, CombatHUD, &ACombatInterfaceHUD::FinishingWork, 1);
}

void ACombatLevel::DestoryAllEnemy()
{
	if (auto World = GetWorld()) {
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(World, AEnemy_Base::StaticClass(), OutActors);
		for (auto actor : OutActors) {
			actor->Destroy();
		}
	}
}

void ACombatLevel::PickupAllAssets()
{
	if (auto World = GetWorld()) {
		TArray<AActor*> OutActors;
		UGameplayStatics::GetAllActorsOfClass(World, AItem_Base::StaticClass(), OutActors);
		for (auto actor : OutActors) {
			if (auto Item = Cast<AItem_Base>(actor)) {
				if (CurCharacter) {
					Item->SetPickUpActor(CurCharacter);
				}
			}
		}
	}
}
