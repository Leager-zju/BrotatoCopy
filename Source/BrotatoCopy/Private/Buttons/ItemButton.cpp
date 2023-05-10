#include "Buttons/ItemButton.h"

#include "Commons/MyGameInstance.h"
#include "HUD/CombatInterfaceHUD.h"
#include "HUD/IntroductionBlock.h"
#include "HUD/RecordBlock.h"
#include "HUD/SelectionWidget.h"
#include "HUD/ShopWidget.h"
#include "HUD/StarterHUD.h"

#include "Components/Button.h"
#include "Components/Image.h"


void UItemButton::NativeConstruct()
{
	Super::NativeConstruct();

	MyGameInstance = Cast<UMyGameInstance>(GetGameInstance());	
	Button->OnHovered.AddDynamic(this, &UItemButton::OnHovered);
	Button->OnClicked.AddDynamic(this, &UItemButton::OnClicked);
	Button->OnUnhovered.AddDynamic(this, &UItemButton::OnUnhovered);
}

void UItemButton::OnHovered()
{
	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			switch (ButtonType)
			{
			case EButtonType::CharacterSelect:
				IntroductionBlock = CreateWidget<UIntroductionBlock>(PC, IntroductionBlockClass);
				RecordBlock = CreateWidget<URecordBlock>(PC, RecordBlockClass);
				if (IntroductionBlock && RecordBlock) {
					IntroductionBlock->SetSelectedInfo(ItemInfo);
					if (auto StarterHUD = Cast<AStarterHUD>(PC->GetHUD())) {
						if (auto SelectionWidget = StarterHUD->GetSelectionWidget()) {
							SelectionWidget->AddChildToShowBox(IntroductionBlock, RecordBlock);
						}
					}
				}
				break;
			case EButtonType::WeaponSelect:
				IntroductionBlock = CreateWidget<UIntroductionBlock>(PC, IntroductionBlockClass);
				if (IntroductionBlock) {
					IntroductionBlock->SetSelectedInfo(ItemInfo);
					if (auto StarterHUD = Cast<AStarterHUD>(PC->GetHUD())) {
						if (auto SelectionWidget = StarterHUD->GetSelectionWidget()) {
							SelectionWidget->AddChildToShowBox(IntroductionBlock);
						}
					}
				}
				break;
			case EButtonType::CharacterComment:
				// TODO
				break;
			case EButtonType::WeaponComment:
				break;
			case EButtonType::PropComment:
				if (auto CombatHUD = Cast<ACombatInterfaceHUD>(PC->GetHUD())) {
					if (auto ShopWidget = CombatHUD->GetShopWidget()) {
						ShopWidget->CreatePropCommentBlock(this);
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

void UItemButton::OnClicked()
{
	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			UE_LOG(LogTemp, Warning, TEXT("Click Button with type: %d, index %d"), ButtonType, SlotIndex);
			switch (ButtonType)
			{
			case EButtonType::CharacterSelect:
				if (MyGameInstance) {
					MyGameInstance->SetSelectedCharacterClass(ItemInfo.ItemClass);
				}
				if (auto StarterHUD = Cast<AStarterHUD>(PC->GetHUD())) {
					StarterHUD->EnterWeaponSelection();
				}
				break;
			case EButtonType::WeaponSelect:
				if (MyGameInstance) {
					MyGameInstance->SetSelectedWeaponClass(ItemInfo.ItemClass);
				}
				if (auto StarterHUD = Cast<AStarterHUD>(PC->GetHUD())) {
					if (auto SelectionWidget = StarterHUD->GetSelectionWidget()) {
						SelectionWidget->EnterDifficultySelection();
					}
				}
				break;
			case EButtonType::WeaponComment:
				if (auto CombatHUD = Cast<ACombatInterfaceHUD>(PC->GetHUD())) {
					if (auto ShopWidget = CombatHUD->GetShopWidget()) {
						ShopWidget->CreateWeaponCommentBlock(this);
					}
				}
				break;
			default:
				break;
			}
		}
	}
}

void UItemButton::OnUnhovered()
{
	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			if (auto CombatHUD = Cast<ACombatInterfaceHUD>(PC->GetHUD())) {
				if (auto ShopWidget = CombatHUD->GetShopWidget()) {
					switch (ButtonType)
					{
					case EButtonType::CharacterComment:
						break;
					case EButtonType::WeaponComment:
						break;
					case EButtonType::PropComment:
						ShopWidget->RemovePropCommentBlock();
						break;
					default:
						break;
					}
				}
			}
		}
	}
}

void UItemButton::SetItemInfo(FItemInfo& Info)
{
	ItemInfo = Info;
	Img->SetBrush(Info.Img);
}
