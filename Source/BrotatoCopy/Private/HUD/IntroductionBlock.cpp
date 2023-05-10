#include "HUD/IntroductionBlock.h"

#include "Commons/ItemInfo.h"

#include "Components/CanvasPanelSlot.h"
#include "Components/Image.h"
#include "Components/SizeBox.h"
#include "Components/TextBlock.h"

void UIntroductionBlock::SetSelectedInfo(FItemInfo& Info)
{
	ItemInfo = Info;
	SetImg(Info.Img);
	SetName(Info.Name);
	SetType(Info.ItemType);
	SetIntroduction(Info.Introduction);
	SetRarity(Info.Rarity);
}

void UIntroductionBlock::SetPosition(FVector2D Pos, FVector2D Alignment /*= { 0, 0 }*/)
{
	if (UCanvasPanelSlot* BlockSlot = Cast<UCanvasPanelSlot>(Block->Slot))
	{
		BlockSlot->SetPosition(Pos);
		BlockSlot->SetAlignment(Alignment);
	}
}

void UIntroductionBlock::SetImg(const FSlateBrush& Brush)
{
	Img->SetBrush(Brush);
}

void UIntroductionBlock::SetName(const FText& txt)
{
	Name->SetText(txt);
}

void UIntroductionBlock::SetType(EType InType)
{
	switch (InType)
	{
	case EType::Character:
		Type->SetText(FText::FromString(TEXT("角色")));
		break;
	case EType::Enemy:
		Type->SetText(FText::FromString(TEXT("敌人")));
		break;
	case EType::Weapon:
		Type->SetText(FText::FromString(TEXT("武器")));
		break;
	case EType::Prop:
		Type->SetText(FText::FromString(TEXT("道具")));
		break;
	case EType::Strengthen:
		Type->SetText(FText::FromString(TEXT("强化")));
		break;
	default:
		break;
	}
}

void UIntroductionBlock::SetIntroduction(const FText& txt)
{
	Introduction->SetText(txt);
}

void UIntroductionBlock::SetRarity(ERarity Rarity)
{
	switch (Rarity) {
	case ERarity::White:
		BackGround->SetColorAndOpacity(FLinearColor(1, 1, 1));
		break;
	case ERarity::Blue:
		BackGround->SetColorAndOpacity(FLinearColor(0, 0, 1));
		break;
	case ERarity::Purple:
		BackGround->SetColorAndOpacity(FLinearColor(0, 1, 0));
		break;
	case ERarity::Red:
		BackGround->SetColorAndOpacity(FLinearColor(1, 0, 0));
		break;
	default:
		BackGround->SetColorAndOpacity(FLinearColor(1, 1, 1));
		break;
	}
}