#include "HUD/ShopWidget.h"

#include "Buttons/ItemButton.h"
#include "Characters/Character_Base.h"
#include "Commons/MyGameInstance.h"
#include "Commons/ItemInfo.h"
#include "HUD/AttributeBlock.h"
#include "HUD/IntroductionBlockWithPurchase.h"
#include "HUD/IntroductionBlockWithSale.h"
#include "LevelScript/CombatLevel.h"
#include "Props/Prop_Base.h"
#include "Weapons/Weapon_Base.h"

#include "Blueprint/WidgetLayoutLibrary.h"
#include "Blueprint/WidgetTree.h"
#include "Components/Button.h"
#include "Components/ScrollBox.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"
#include "Components/WrapBox.h"
#include "Kismet/GameplayStatics.h"

void UShopWidget::NativeConstruct()
{
	Super::NativeConstruct();

	RefreshButton->OnClicked.AddDynamic(this, &UShopWidget::Refresh);
	NextRound->OnClicked.AddDynamic(this, &UShopWidget::BeginNewRound);

	MyGameIns = Cast<UMyGameInstance>(GetGameInstance());
	if (auto World = GetWorld()) {
		CombatLevel = Cast<ACombatLevel>(World->GetLevel(0));
	}

	CommodityBoxes.Init(nullptr, 4);
	for (int i = 0; i < 4; i++) {
		if (auto Box = Cast<USizeBox>(GetWidgetFromName(*("CommodityBox" + FString::FromInt(i + 1))))) {
			CommodityBoxes[i] = Box;
		}
	}

	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			AttributeBlock = CreateWidget<UAttributeBlock>(PC, AttributeBlockClass);
			if (AttributeBlock) {
				AttributeBox->AddChild(AttributeBlock);
			}
		}
	}

	Refresh();
}

void UShopWidget::SetCurAsset(int Value)
{
	CurAsset->SetText(FText::FromString(FString::FromInt(Value)));
}

void UShopWidget::ItemGetPurchaseAtIndex(int Index)
{
	CommodityBoxes[Index]->ClearChildren();
	NumofCommodity--;

	if (NumofCommodity == 0) {
		SetFreeRefreshTime(1);
	}
}

void UShopWidget::SetRound(int Value)
{
	ShopRound->SetText(FText::FromString(TEXT("商店（第") + FString::FromInt(Value) + TEXT("波）")));
}

void UShopWidget::Refresh()
{
	NumofCommodity = 4;
	if (auto World = GetWorld()) {
		if (auto CurCharacter = Cast<ACharacter_Base>(UGameplayStatics::GetPlayerPawn(World, 0))) {
			if (CurCharacter->GetMainAttribute().Assets < GetRefreshCost()) {
				SetUnaffordble();
				return;
			}
			CurCharacter->TakeCost(GetRefreshCost());
			if (auto PC = World->GetFirstPlayerController()) {
				if (MyGameIns) {
					CreateCommodityBlock(PC);
				}
			}
		}
	}

	if (FreeRefreshTime) {
		FreeRefreshTime--;
	}

	if (FreeRefreshTime == 0) {
		SetRefreshCost(RefreshCost + 1);
	}
}

void UShopWidget::CreateCommodityBlock(APlayerController* PC)
{
	TArray<UClass*> AppearedCommodityClass;
	for (int i = 0; i < 4; i++) {
		if (auto CommodityBlock = CreateWidget<UIntroductionBlockWithPurchase>(PC, CommodityBlockClass)) {
			UClass* CommodityClass = MyGameIns->RandomWeaponPropClass();
			//TODO: 去除重复强化
			/*while (AppearedCommodityClass.Find(CommodityClass) != INDEX_NONE) {
				CommodityClass = MyGameIns->RandomWeaponPropClass();
			}
			AppearedCommodityClass.Add(CommodityClass);*/

			if (auto Weapon = Cast<AWeapon_Base>(CommodityClass->GetDefaultObject(false))) {
				ERarity Rarity = ERarity::White; // TODO: 按概率设置品质
				CommodityBlock->SetSelectedInfo(Weapon->GetInfo(Rarity));// 武器默认白色品质，需根据概率手动设置
			}
			else if (auto Prop = Cast<AProp_Base>(CommodityClass->GetDefaultObject(false))) {
				CommodityBlock->SetSelectedInfo(Prop->GetInfo());
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("Wrong Class: %s"), *(CommodityClass->GetName()));
				continue;
			}

			CommodityBlock->SetParent(this);
			CommodityBlock->SetCost(1);
			CommodityBlock->SetIndex(i);
			if (CommodityBoxes[i]) {
				CommodityBoxes[i]->ClearChildren();
				CommodityBoxes[i]->AddChild(CommodityBlock);
			}
		}
	}
}

void UShopWidget::BeginNewRound()
{
	if (CombatLevel) {
		CombatLevel->BeginNewRound();
	}
}

void UShopWidget::SetRefreshCost(int Value)
{
	RefreshCost = Value;
	RefreshCostText->SetText(FText::FromString(TEXT("刷新-") + FString::FromInt(RefreshCost)));
}

void UShopWidget::SetFreeRefreshTime(int Value)
{
	FreeRefreshTime = Value;
	if (FreeRefreshTime) {
		RefreshCostText->SetText(FText::FromString("0"));
	}
}

void UShopWidget::UpdateAttributeBox(FCharacterMainAttribute& MainAttr, FCharacterSecondaryAttribute& SecondaryAttr)
{
	if (AttributeBlock) {
		AttributeBlock->UpdateAttr(MainAttr, SecondaryAttr);
	}
}

void UShopWidget::UpdateProps(TArray<FPropInfo>& PropsOwned)
{
	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			UWrapBox* Row = WidgetTree->ConstructWidget<UWrapBox>(UWrapBox::StaticClass());
			if (!Row) return;
			
			PropBox->ClearChildren();

			const int MaxNumofButtonsInRow = 10;
			int CurNumInRow = 0;
			for (auto&& PropInfo : PropsOwned) {
				UItemButton* Button = CreateWidget<UItemButton>(PC, ItemButtonClass);
				if (Button) {
					if (auto Prop = Cast<AProp_Base>(PropInfo.PropClass->GetDefaultObject(false))) {
						Button->SetItemInfo(Prop->GetInfo());
					}
					Button->SetType(EButtonType::PropComment);

					Row->AddChild(Button);
					if (++CurNumInRow == MaxNumofButtonsInRow) {
						PropBox->AddChild(Row);
						Row = WidgetTree->ConstructWidget<UWrapBox>(UWrapBox::StaticClass());
						if (!Row) return;

						CurNumInRow = 0;
					}
				}
			}
			if (CurNumInRow) {
				PropBox->AddChild(Row);
			}
		}
	}
}

void UShopWidget::UpdateWeapons(TArray<FWeaponInfo>& WeaponsOwned)
{
	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			UWrapBox* Row = WidgetTree->ConstructWidget<UWrapBox>(UWrapBox::StaticClass());
			if (!Row) return;

			WeaponBox->ClearChildren();

			const int MaxNumofButtonsInRow = 3;
			int CurNumInRow = 0;
			int Index = 0;
			for (auto&& WeaponInfo : WeaponsOwned) {
				UClass* WeaponClass = WeaponInfo.WeaponClass;
				if (!WeaponClass) break;

				UItemButton* Button = CreateWidget<UItemButton>(PC, ItemButtonClass);
				if (Button) {
					if (auto Weapon = Cast<AWeapon_Base>(WeaponClass->GetDefaultObject(false))) {
						Button->SetItemInfo(Weapon->GetInfo(WeaponInfo.Rarity));
					}
					Button->SetType(EButtonType::WeaponComment);
					Button->SetSlotIndex(Index++);

					Row->AddChild(Button);
					if (++CurNumInRow == MaxNumofButtonsInRow) {
						WeaponBox->AddChild(Row);
						Row = WidgetTree->ConstructWidget<UWrapBox>(UWrapBox::StaticClass());
						if (!Row) return;

						CurNumInRow = 0;
					}
				}
			}
			if (CurNumInRow) {
				WeaponBox->AddChild(Row);
			}
		}
	}
}

void UShopWidget::CreatePropCommentBlock(UItemButton* Button)
{
	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			PropCommentBlock = CreateWidget<UIntroductionBlock>(PC, PropCommentblockClass);
			if (PropCommentBlock) {
				const FGeometry& ParentGeometry = GetCachedGeometry();
				const FGeometry& ButtonGeometry = Button->GetCachedGeometry();
				FVector2D Position = ParentGeometry.AbsoluteToLocal(ButtonGeometry.GetAbsolutePosition()) + ButtonGeometry.GetLocalSize();
				PropCommentBlock->SetPosition(Position, { 0, 1 });
				PropCommentBlock->SetSelectedInfo(Button->GetItemInfo());
				PropCommentBlock->AddToViewport();
			}
		}
	}
}

void UShopWidget::RemovePropCommentBlock()
{
	if (PropCommentBlock) {
		PropCommentBlock->RemoveFromParent();
	}
}

void UShopWidget::CreateWeaponCommentBlock(UItemButton* Button)
{
	if (WeaponCommentBlock) {
		WeaponCommentBlock->RemoveFromParent();
	}
	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			WeaponCommentBlock = CreateWidget<UIntroductionBlockWithSale>(PC, WeaponCommentblockClass);
			if (WeaponCommentBlock) {
				const FGeometry& ParentGeometry = GetCachedGeometry();
				const FGeometry& ButtonGeometry = Button->GetCachedGeometry();
				FVector2D Position = ParentGeometry.AbsoluteToLocal(ButtonGeometry.GetAbsolutePosition()) + ButtonGeometry.GetLocalSize();
				WeaponCommentBlock->SetPosition(Position, { 0, 1 });
				WeaponCommentBlock->SetSelectedInfo(Button->GetItemInfo());
				WeaponCommentBlock->SetSlotIndex(Button->GetSlotIndex());
				WeaponCommentBlock->SetSalePrice(1);	// TODO: Generate Sale Price
				WeaponCommentBlock->AddToViewport();
			}
		}
	}
}

void UShopWidget::RemoveWeaponCommentBlock()
{
	if (WeaponCommentBlock) {
		WeaponCommentBlock->RemoveFromParent();
	}
}

void UShopWidget::SetUnaffordble()
{
	// TODO
}