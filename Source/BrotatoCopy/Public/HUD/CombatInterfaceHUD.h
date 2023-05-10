#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "CombatInterfaceHUD.generated.h"

class ACharacter_Base;
class ACombatLevel;
struct FCharacterMainAttribute;
struct FCharacterSecondaryAttribute;
struct FPropInfo;
struct FWeaponInfo;
class UCombatInterfaceWidget;
class UGetPropWidget;
class UShopWidget;
class UStrengthenWidget;

UCLASS()
class BROTATOCOPY_API ACombatInterfaceHUD : public AHUD
{
	GENERATED_BODY()

public:
	void FinishingWork();
	void EnterCombat();
	void EnterShop();

	void SetHealthBarPercent(float Percent);
	void SetCurHealth(int Value);
	void SetMaxHealth(int Value);
	void SetExpBarPercent(float Percent);
	void SetLevel(int Value);
	void SetCurAsset(int Value);
	void SetUnpicked(int Value);
	void SetRound(int CurRound);
	void UpdateCountDown(int CountDown);
	void UpdateProps(TArray<FPropInfo>& Props);
	void UpdateWeapons(TArray<FWeaponInfo>& Weapons);
	void UpdateAttr(FCharacterMainAttribute& MainAttr, FCharacterSecondaryAttribute& SecondaryAttr);

	void AddStrengthenTime();
	void CharacterGetStrengthen();
	void AddChestCount(int Quality);
	void CharacterGetRandomProp();

	UShopWidget* GetShopWidget() { return ShopWidget; }

private:
	/**
	 * Combat Interface
	 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UCombatInterfaceWidget> CombatInterfaceWidgetClass;

	UPROPERTY(VisibleAnywhere)
	UCombatInterfaceWidget* CombatInterfaceWidget;
	
	/**
	 * Shop
	 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UShopWidget> ShopWidgetClass;

	UPROPERTY(VisibleAnywhere)
	UShopWidget* ShopWidget;

	/**
	 * Strengthen
	 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UStrengthenWidget> StrengthenWidgetClass;

	UPROPERTY(VisibleAnywhere)
	UStrengthenWidget* StrengthenWidget;

	/**
	 * Get Prop
	 */
	UPROPERTY(EditAnywhere)
	TSubclassOf<UGetPropWidget> GetPropWidgetClass;

	UPROPERTY(VisibleAnywhere)
	UGetPropWidget* GetPropWidget;

private:
	UPROPERTY(VisibleAnywhere)
	int StrengthenTime{0};
	
	UPROPERTY(VisibleAnywhere)
	int NumofChest{0};

	UPROPERTY(VisibleAnywhere)
	int Round;
};
