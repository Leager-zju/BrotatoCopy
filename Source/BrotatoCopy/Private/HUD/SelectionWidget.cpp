#include "HUD/SelectionWidget.h"
#include "HUD/StarterHUD.h"
#include "Components/WrapBox.h"
#include "Components/TextBlock.h"
#include "Commons/MyGameInstance.h"
#include "Kismet/GameplayStatics.h"


void USelectionWidget::NativeConstruct() // 首先进入角色选择界面
{	
	Super::NativeConstruct();

	Title->SetText(FText::FromString(TEXT("角色选择")));

	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());
	if (MyGameInstance) {
		FillSelectBox<EButtonType::CharacterSelect>(MyGameInstance->GetCharacterClasses(), SelectButtonClass, EType::Character);
	}

	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			StarterHUD = Cast<AStarterHUD>(PC->GetHUD());
		}
	}
}

// only called from character selection
void USelectionWidget::AddChildToShowBox(UWidget* Widget1, UWidget* Widget2)
{
	if (Widget1 && Widget2) {
		ShowBox->ClearChildren();
		ShowBox->AddChild(Widget1);
		ShowBox->AddChild(Widget2);
	}
}

// called from weapon/difficulty selection
void USelectionWidget::AddChildToShowBox(UWidget* Widget)
{
	if (Widget) {
		if (int Count = ShowBox->GetChildrenCount(); Count > 1) {
			ShowBox->RemoveChildAt(Count - 1);
		}
		ShowBox->AddChild(Widget);
	}
}

void USelectionWidget::BackToCharacterSelection()
{
	Title->SetText(FText::FromString(TEXT("角色选择")));
	ShowBox->ClearChildren();

	if (MyGameInstance) {
		FillSelectBox<EButtonType::CharacterSelect>(MyGameInstance->GetCharacterClasses(), SelectButtonClass, EType::Character);
	}
}

void USelectionWidget::EnterWeaponSelection()
{
	Title->SetText(FText::FromString(TEXT("武器选择")));
	if (ShowBox->GetChildAt(1)) {	// Remove Record Block
		ShowBox->RemoveChildAt(1);
	}

	if (MyGameInstance) {
		FillSelectBox<EButtonType::WeaponSelect>(MyGameInstance->GetWeaponOwned(), SelectButtonClass, EType::Weapon);
	}
}

void USelectionWidget::BackToWeaponSelection()
{
	Title->SetText(FText::FromString(TEXT("武器选择")));
	if (ShowBox->GetChildAt(2)) {	// Remove Difficulty Block
		ShowBox->RemoveChildAt(2);
	}

	if (MyGameInstance) {
		FillSelectBox<EButtonType::WeaponSelect>(MyGameInstance->GetWeaponOwned(), SelectButtonClass, EType::Weapon);
	}
}

void USelectionWidget::EnterDifficultySelection()
{
	Title->SetText(FText::FromString(TEXT("难度选择")));
	// TODO

	if (auto World = GetWorld()) {
		UGameplayStatics::OpenLevel(World, "Combat");
	}
}

template<EButtonType ButtonType>
void USelectionWidget::FillSelectBox(TArray<UClass*>& Classes, TSubclassOf<UItemButton> ButtonClass, EType ItemType)
{
	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			if (SelectBox && ButtonClass) {
				SelectBox->ClearChildren();

				for (auto&& ItemClass : Classes) {
					UItemButton* Button = CreateWidget<UItemButton>(PC, ButtonClass);
					if (Button) {
						if (ItemType == EType::Character) {
							if (auto Character = Cast<ACharacter_Base>(ItemClass->GetDefaultObject(false))) {
								Button->SetItemInfo(Character->GetInfo());
							}
						}
						else if (ItemType == EType::Weapon) {
							if (auto Weapon = Cast<AWeapon_Base>(ItemClass->GetDefaultObject(false))) {
								Button->SetItemInfo(Weapon->GetInfo(ERarity::White));
							}
						}
						else {
							UE_LOG(LogTemp, Warning, TEXT("[Selection]: Wrong Button Type: %d"), ItemType);
							continue;
						}
						Button->SetType(ButtonType);
						SelectBox->AddChild(Button);
					}
				}
			}
		}
	}
}