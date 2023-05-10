#include "HUD/IntroductionBlockWithPurchase.h"

#include "Characters/Character_Base.h"
#include "HUD/CombatInterfaceHUD.h"
#include "Interface/PurchaseWidgetInterface.h"
#include "Props/Prop_Base.h"
#include "Strengthens/Strengthen_Base.h"
#include "Weapons/Weapon_Base.h"

#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UIntroductionBlockWithPurchase::NativeConstruct()
{
	Super::NativeConstruct();

	PurchaseButton->OnClicked.AddDynamic(this, &UIntroductionBlockWithPurchase::Purchase);
}

void UIntroductionBlockWithPurchase::Purchase()
{
	if (auto World = GetWorld()) {
		if (auto CurCharacter = Cast<ACharacter_Base>(UGameplayStatics::GetPlayerPawn(World, 0))) {
			if (ItemInfo.ItemType == EType::Prop) {
				if (auto Obj = Cast<AProp_Base>(ItemInfo.ItemClass->GetDefaultObject(false))) {
					Obj->BePurchasedBy(CurCharacter, PurchaseCost);
				}
				else {
					UE_LOG(LogTemp, Warning, TEXT("[Commodity]: Cast To Prop Failed"));
				}
			}
			else if (ItemInfo.ItemType == EType::Weapon) {
				if (ItemInfo.ItemClass->IsChildOf(AWeapon_Base::StaticClass())) {
					CurCharacter->BuyWeapon(FWeaponInfo(ItemInfo.ItemClass, ItemInfo.Rarity), PurchaseCost);
				}
				else {
					UE_LOG(LogTemp, Warning, TEXT("[Commodity]: Cast To Weapon Failed"));
				}
			}
			else if (ItemInfo.ItemType == EType::Strengthen) {
				if (auto Obj = Cast<AStrengthen_Base>(ItemInfo.ItemClass->GetDefaultObject(false))) {
					Obj->BePurchasedBy(CurCharacter);
				}
				else {
					UE_LOG(LogTemp, Warning, TEXT("[Commodity]: Cast To Strengthen Failed"));
				}
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("[Commodity]: Wrong Item Type: %d"), ItemInfo.ItemType);
			}

			if (auto p = Cast<IPurchaseWidgetInterface>(Parent)) {
				p->ItemGetPurchaseAtIndex(SlotIndex);
			}
		}
	}
}

void UIntroductionBlockWithPurchase::SetCost(int Cost)
{
	PurchaseCost = Cost;
	PurchaseCostText->SetText(FText::FromString(FString::FromInt(Cost)));
}
