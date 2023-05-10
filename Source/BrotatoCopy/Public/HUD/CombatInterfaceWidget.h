// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "CombatInterfaceWidget.generated.h"

class UProgressBar;
class UTextBlock;
class UWrapBox;
struct FSlateBrush;

UCLASS()
class BROTATOCOPY_API UCombatInterfaceWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	void SetHealthBarPercent(float Percent);
	void SetCurHealth(int Value);
	void SetMaxHealth(int Value);
	void SetExpBarPercent(float Percent);
	void SetLevel(int Value);
	void SetCurAsset(int Value);
	void SetUnpicked(int Value);
	void SetRound(int CurRound);
	void SetCountDown(int cd);
	void UpdateCountDown();
	void IncreaseStrengthenTime();
	void DecreaseStrengthenTime();
	void IncreaseNumofChest(int Quality);
	void DecreaseNumofChest();
	
private:
	UPROPERTY(meta = (BindWidget))
	UProgressBar* HealthBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CurHealth;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* MaxHealth;

	UPROPERTY(meta = (BindWidget))
	UProgressBar* ExpBar;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Level;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Assets;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Unpicked;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Round;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* CountDown;
	
	UPROPERTY(meta = (BindWidget))
	UWrapBox* StrengthenBox;

	UPROPERTY(meta = (BindWidget))
	UWrapBox* ChestBox;

	UPROPERTY(EditAnywhere)
	FSlateBrush StrengthenImage;

	UPROPERTY(EditAnywhere)
	FSlateBrush NormalChestImage;

	UPROPERTY(EditAnywhere)
	FSlateBrush RareChestImage;

	// Timer
	FTimerHandle UpdateCountDownTimer;

	int CD;
};
