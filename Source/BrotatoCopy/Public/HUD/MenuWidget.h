// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MenuWidget.generated.h"

class AStarterHUD;
class UButton;

UCLASS()
class BROTATOCOPY_API UMenuWidget : public UUserWidget
{
	GENERATED_BODY()

public:
	virtual void NativeConstruct();

	UFUNCTION()
	void StartButtonClicked();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* StartButton;

	AStarterHUD* StarterHUD;
};
