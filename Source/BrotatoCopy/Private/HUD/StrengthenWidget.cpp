#include "HUD/StrengthenWidget.h"

#include "Characters/Character_Base.h"
#include "Commons/MyGameInstance.h"
#include "HUD/CombatInterfaceHUD.h"
#include "HUD/IntroductionBlockWithPurchase.h"
#include "Strengthens/Strengthen_Base.h"

#include "Components/WrapBox.h"
#include "Components/Button.h"
#include "Components/TextBlock.h"
#include "Kismet/GameplayStatics.h"

void UStrengthenWidget::NativeConstruct()
{
	Super::NativeConstruct();

	MyGameIns = Cast<UMyGameInstance>(GetGameInstance());

	RefreshButton->OnClicked.AddDynamic(this, &UStrengthenWidget::Refresh);

	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			CombatHUD = Cast<ACombatInterfaceHUD>(PC->GetHUD());
		}
	}

	Refresh();	// 初始进行一次免费刷新
}

void UStrengthenWidget::SetCurAsset(int Value)
{
	CurAsset->SetText(FText::FromString(FString::FromInt(Value)));
}

void UStrengthenWidget::ItemGetPurchaseAtIndex(int Index)
{
	StrengthenBox->RemoveChildAt(Index);
	if (CombatHUD) {
		CombatHUD->FinishingWork();
	}
}

void UStrengthenWidget::SetRefreshCost(int Value)
{
	RefreshCost = Value;
	RefreshCostText->SetText(FText::FromString(FString::FromInt(RefreshCost)));
}

void UStrengthenWidget::Refresh()
{
	if (auto World = GetWorld()) {
		if (auto CurCharacter = Cast<ACharacter_Base>(UGameplayStatics::GetPlayerPawn(World, 0))) {
			if (CurCharacter->GetMainAttribute().Assets < RefreshCost) {
				SetUnaffordble();
				return;
			}
			CurCharacter->TakeCost(RefreshCost);
			if (auto PC = World->GetFirstPlayerController()) {
				if (MyGameIns) {
					CreateStrengthenBlock(PC);
				}
			}
		}
	}

	SetRefreshCost(RefreshCost + 1);
}


void UStrengthenWidget::CreateStrengthenBlock(APlayerController* PC)
{	
	StrengthenBox->ClearChildren();
	TArray<UClass*> AppearedStrengthenClass;
	for (int i = 0; i < 4; i++) {
		if (auto StrengthenBlock = CreateWidget<UIntroductionBlockWithPurchase>(PC, StrengthenBlockClass)) {
			UClass* StrengthenClass = MyGameIns->RandomStrengthenClass();

			//TODO: 去除重复强化
			/*while (AppearedStrengthenClass.Find(StrengthenClass) != INDEX_NONE) {
				StrengthenClass = MyGameIns->RandomStrengthenClass();
			}
			AppearedStrengthenClass.Add(StrengthenClass);*/

			if (auto Strengthen = Cast<AStrengthen_Base>(StrengthenClass->GetDefaultObject(false))) {
				StrengthenBlock->SetSelectedInfo(Strengthen->GetInfo());
			}
			else {
				UE_LOG(LogTemp, Warning, TEXT("[Strengthen]: Wrong Class: %s"), *(StrengthenClass->GetName()));
				continue;
			}
			StrengthenBlock->SetParent(this);
			StrengthenBlock->SetCost(0);	// 强化是免费
			StrengthenBlock->SetIndex(i);
			StrengthenBox->AddChild(StrengthenBlock);
		}
	}
}

// TODO: 将所有购买按钮设为不可点击，且字体为红
void UStrengthenWidget::SetUnaffordble()
{

}

