#include "HUD/CombatInterfaceWidget.h"

#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Image.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Styling/SlateBrush.h"


void UCombatInterfaceWidget::SetHealthBarPercent(float Percent)
{
	HealthBar->SetPercent(Percent);
}

void UCombatInterfaceWidget::SetCurHealth(int Value)
{
	CurHealth->SetText(FText::FromString(FString::FromInt(Value)));
}

void UCombatInterfaceWidget::SetMaxHealth(int Value)
{
	MaxHealth->SetText(FText::FromString(FString::FromInt(Value)));
}

void UCombatInterfaceWidget::SetExpBarPercent(float Percent)
{
	ExpBar->SetPercent(Percent);
}

void UCombatInterfaceWidget::SetLevel(int Value)
{
	Level->SetText(FText::FromString(FString::Printf(TEXT("Lv. %d"), Value)));
}

void UCombatInterfaceWidget::SetCurAsset(int Value)
{
	Assets->SetText(FText::FromString(FString::FromInt(Value)));
}

void UCombatInterfaceWidget::SetUnpicked(int Value)
{
	Unpicked->SetText(FText::FromString(FString::FromInt(Value)));
}

void UCombatInterfaceWidget::SetRound(int CurRound)
{
	Round->SetText(FText::FromString(FString::Printf(TEXT("第 %d 波"), CurRound)));
}

void UCombatInterfaceWidget::SetCountDown(int cd)
{
	CD = cd;
	UpdateCountDown();
}

void UCombatInterfaceWidget::UpdateCountDown()
{
	CountDown->SetText(FText::FromString(FString::FromInt(CD)));
	
	if (CD--) {
		if (auto World = GetWorld()) {
			auto&& TimerManager = World->GetTimerManager();
			TimerManager.SetTimer(UpdateCountDownTimer, this, &UCombatInterfaceWidget::UpdateCountDown, 1);
		}
	}
}

void UCombatInterfaceWidget::IncreaseStrengthenTime()
{
	if (auto World = GetWorld()) {
		if (UImage* Image = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass())) {
			Image->SetBrush(StrengthenImage);
			StrengthenBox->AddChildToWrapBox(Image);
		}
	}
}

void UCombatInterfaceWidget::DecreaseStrengthenTime()
{
	if (StrengthenBox->GetChildrenCount() > 0) {
		StrengthenBox->RemoveChildAt(StrengthenBox->GetChildrenCount() - 1);
	}
}

void UCombatInterfaceWidget::IncreaseNumofChest(int Quality)
{
	if (auto World = GetWorld()) {
		if (UImage* Image = WidgetTree->ConstructWidget<UImage>(UImage::StaticClass())) {
			Image->SetBrush(Quality ? RareChestImage : NormalChestImage);
			ChestBox->AddChildToWrapBox(Image);
		}
	}
}

void UCombatInterfaceWidget::DecreaseNumofChest()
{
	if (ChestBox->GetChildrenCount() > 0) {
		ChestBox->RemoveChildAt(ChestBox->GetChildrenCount() - 1);
	}
}
