#include "HUD/CombatInterfaceHUD.h"

#include "Characters/Character_Base.h"
#include "GameMode/CombatGameMode.h"
#include "HUD/CombatInterfaceWidget.h"
#include "HUD/StrengthenWidget.h"
#include "HUD/GetPropWidget.h"
#include "HUD/ShopWidget.h"

#include "Kismet/GameplayStatics.h"

void ACombatInterfaceHUD::FinishingWork()
{
	if (StrengthenTime) {
		CharacterGetStrengthen();
	}
	else if (NumofChest) {
		CharacterGetRandomProp();
	}
	else {
		EnterShop();
	}
}

void ACombatInterfaceHUD::EnterCombat()
{
	if (ShopWidget) {
		ShopWidget->RemoveFromParent();
	}
	UE_LOG(LogTemp, Warning, TEXT("[HUD]: Enter Combat"));
	StrengthenTime = 0;
	if (auto World = GetWorld()) {
		CombatInterfaceWidget = CreateWidget<UCombatInterfaceWidget>(World, CombatInterfaceWidgetClass);
		if (CombatInterfaceWidget) {
			CombatInterfaceWidget->SetRound(Round);
			CombatInterfaceWidget->AddToViewport();
		}
	}
}

void ACombatInterfaceHUD::EnterShop()
{
	if (CombatInterfaceWidget) {
		CombatInterfaceWidget->RemoveFromParent();
	}
	if (StrengthenWidget) {
		StrengthenWidget->RemoveFromParent();
	}
	if (GetPropWidget) {
		GetPropWidget->RemoveFromParent();
	}

	UE_LOG(LogTemp, Warning, TEXT("[HUD]: Enter Shop"));
	if (auto World = GetWorld()) {
		if (auto Character = Cast<ACharacter_Base>(UGameplayStatics::GetPlayerPawn(World, 0))) {
			ShopWidget = CreateWidget<UShopWidget>(World, ShopWidgetClass);
			if (ShopWidget) {
				ShopWidget->SetRound(Round);
				ShopWidget->UpdateProps(Character->GetPropsOwned());
				ShopWidget->UpdateWeapons(Character->GetWeaponOwned());
				ShopWidget->AddToViewport();
			}
		}
	}
}

void ACombatInterfaceHUD::CharacterGetStrengthen()
{
	if (StrengthenWidget) {
		ShopWidget->RemoveFromParent();
	}
	if (CombatInterfaceWidget) {
		CombatInterfaceWidget->DecreaseStrengthenTime();
	}
	StrengthenTime--;
	UE_LOG(LogTemp, Warning, TEXT("[HUD]: Character Get Strengthen"));
	if (auto World = GetWorld()) {
		StrengthenWidget = CreateWidget<UStrengthenWidget>(World, StrengthenWidgetClass);
		if (StrengthenWidget) {
			StrengthenWidget->AddToViewport();
		}
	}
}

void ACombatInterfaceHUD::CharacterGetRandomProp()
{
	UE_LOG(LogTemp, Warning, TEXT("[HUD]: Character Get Random Prop"));
	if (auto World = GetWorld()) {
		GetPropWidget = CreateWidget<UGetPropWidget>(World, GetPropWidgetClass);
		if (GetPropWidget) {
			GetPropWidget->AddToViewport();
		}
	}
}

void ACombatInterfaceHUD::SetHealthBarPercent(float Percent)
{
	if (CombatInterfaceWidget) {
		CombatInterfaceWidget->SetHealthBarPercent(Percent);
	}
}

void ACombatInterfaceHUD::SetCurHealth(int Value)
{
	if (CombatInterfaceWidget) {
		CombatInterfaceWidget->SetCurHealth(Value);
	}
}

void ACombatInterfaceHUD::SetMaxHealth(int Value)
{
	if (CombatInterfaceWidget) {
		CombatInterfaceWidget->SetMaxHealth(Value);
	}
}

void ACombatInterfaceHUD::SetExpBarPercent(float Percent)
{
	if (CombatInterfaceWidget) {
		CombatInterfaceWidget->SetExpBarPercent(Percent);
	}
}

void ACombatInterfaceHUD::SetLevel(int Value)
{
	if (CombatInterfaceWidget) {
		CombatInterfaceWidget->SetLevel(Value);
	}
}

void ACombatInterfaceHUD::SetCurAsset(int Value)
{
	if (CombatInterfaceWidget) {
		CombatInterfaceWidget->SetCurAsset(Value);
	}
	if (StrengthenWidget) {
		StrengthenWidget->SetCurAsset(Value);
	}
	if (ShopWidget) {
		ShopWidget->SetCurAsset(Value);
	}
}

void ACombatInterfaceHUD::SetUnpicked(int Value)
{
	if (CombatInterfaceWidget) {
		CombatInterfaceWidget->SetUnpicked(Value);
	}
}

void ACombatInterfaceHUD::SetRound(int CurRound)
{
	Round = CurRound;
}

void ACombatInterfaceHUD::UpdateCountDown(int CountDown)
{
	if (CombatInterfaceWidget) {
		CombatInterfaceWidget->SetCountDown(CountDown);
	}
}

void ACombatInterfaceHUD::UpdateProps(TArray<FPropInfo>& Props)
{
	if (ShopWidget) {
		ShopWidget->UpdateProps(Props);
	}
}

void ACombatInterfaceHUD::UpdateWeapons(TArray<FWeaponInfo>& Weapons)
{
	if (ShopWidget) {
		ShopWidget->UpdateWeapons(Weapons);
	}
}

void ACombatInterfaceHUD::UpdateAttr(FCharacterMainAttribute& MainAttr, FCharacterSecondaryAttribute& SecondaryAttr)
{
	if (ShopWidget) {
		ShopWidget->UpdateAttributeBox(MainAttr, SecondaryAttr);
	}
}

void ACombatInterfaceHUD::AddStrengthenTime()
{
	if (CombatInterfaceWidget) {
		StrengthenTime++;
		CombatInterfaceWidget->IncreaseStrengthenTime();
	}
}

void ACombatInterfaceHUD::AddChestCount(int Quality)
{
	if (CombatInterfaceWidget) {
		CombatInterfaceWidget->IncreaseNumofChest(Quality);
	}
}