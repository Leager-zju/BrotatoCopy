#include "HUD/AttributeBlock.h"

#include "Characters/Character_Base.h"
#include "HUD/MainAttributeTextBlock.h"

#include "Components/Button.h"
#include "Components/SizeBox.h"
#include "Kismet/GameplayStatics.h"

void UAttributeBlock::NativeConstruct()
{
	Super::NativeConstruct();
	Main->OnClicked.AddDynamic(this, &UAttributeBlock::SwitchToMain);
	Secondary->OnClicked.AddDynamic(this, &UAttributeBlock::SwitchToSecondary);

	SwitchToMain();
}

void UAttributeBlock::UpdateAttr(FCharacterMainAttribute& MainAttr, FCharacterSecondaryAttribute& SecondaryAttr)
{
	if (bIsMain) {
		if (MainAttributeTextBlock) {
			UpdateMainAttr(MainAttr);
		}
	}
	else {
		UpdateSecondaryAttr(SecondaryAttr);
	}
}

void UAttributeBlock::UpdateMainAttr(FCharacterMainAttribute& MainAttr)
{
	MainAttributeTextBlock->UpdateAttr(MainAttr);
}

void UAttributeBlock::UpdateSecondaryAttr(FCharacterSecondaryAttribute& SecondaryAttr)
{

}

void UAttributeBlock::SwitchToMain()
{
	bIsMain = true;
	if (auto World = GetWorld()) {
		if (auto PC = World->GetFirstPlayerController()) {
			if (MainAttributeTextBlockClass) {
				MainAttributeTextBlock = CreateWidget<UMainAttributeTextBlock>(PC, MainAttributeTextBlockClass);
				if (MainAttributeTextBlock) {
					ShowBox->ClearChildren();
					if (auto CurCharacter = Cast<ACharacter_Base>(UGameplayStatics::GetPlayerPawn(World, 0))) {
						MainAttributeTextBlock->UpdateAttr(CurCharacter->GetMainAttribute());
					}
					ShowBox->AddChild(MainAttributeTextBlock);
				}
			}
		}
	}
}

void UAttributeBlock::SwitchToSecondary()
{
	bIsMain = false;
}
