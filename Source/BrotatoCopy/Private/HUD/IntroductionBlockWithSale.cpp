#include "HUD/IntroductionBlockWithSale.h"

#include "Characters/Character_Base.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "HUD/CombatInterfaceHUD.h"
#include "HUD/ShopWidget.h"

#include "Kismet/GameplayStatics.h"

void UIntroductionBlockWithSale::NativeConstruct()
{
	Super::NativeConstruct();

	CompositeButton->OnClicked.AddDynamic(this, &UIntroductionBlockWithSale::Composite);
	SaleButton->OnClicked.AddDynamic(this, &UIntroductionBlockWithSale::Sale);
	CancelButton->OnClicked.AddDynamic(this, &UIntroductionBlockWithSale::Cancel);
}

void UIntroductionBlockWithSale::SetSalePrice(int Price)
{
	SalePrice = Price;
	PriceText->SetText(FText::FromString(TEXT("卖出+") + FString::FromInt(Price)));
}

void UIntroductionBlockWithSale::Composite()
{
	if (auto World = GetWorld()) {
		
		if (auto PC = GetWorld()->GetFirstPlayerController()) {
			if (auto CombatHUD = Cast<ACombatInterfaceHUD>(PC->GetHUD())) {
				if (auto Character = Cast<ACharacter_Base>(UGameplayStatics::GetPlayerPawn(World, 0))) {
					if (Character->CompositeWeapon(SlotIndex) != -1) {
						CombatHUD->UpdateWeapons(Character->GetWeaponOwned());
					}
				}
				if (auto ShopWidget = CombatHUD->GetShopWidget()) {
					ShopWidget->RemoveWeaponCommentBlock();
				}
			}
		}
	}
}

void UIntroductionBlockWithSale::Sale()
{
	if (auto World = GetWorld()) {
		if (auto Character = Cast<ACharacter_Base>(UGameplayStatics::GetPlayerPawn(World, 0))) {
			Character->SellWeapon(SlotIndex, SalePrice);
		}
		if (auto PC = GetWorld()->GetFirstPlayerController()) {
			if (auto HUD = Cast<ACombatInterfaceHUD>(PC->GetHUD())) {
				if (auto ShopWidget = HUD->GetShopWidget()) {
					ShopWidget->RemoveWeaponCommentBlock();
				}
			}
		}
	}
}

void UIntroductionBlockWithSale::Cancel()
{
	if (auto World = GetWorld()) {
		if (auto PC = GetWorld()->GetFirstPlayerController()) {
			if (auto HUD = Cast<ACombatInterfaceHUD>(PC->GetHUD())) {
				if (auto ShopWidget = HUD->GetShopWidget()) {
					ShopWidget->RemoveWeaponCommentBlock();
				}
			}
		}
	}
}
