#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "Commons/ItemInfo.h"
#include "IntroductionBlock.generated.h"

struct FSlateBrush;
class UImage;
class USizeBox;
class UTextBlock;

UCLASS()
class BROTATOCOPY_API UIntroductionBlock : public UUserWidget
{
	GENERATED_BODY()
public:
	void SetSelectedInfo(FItemInfo& Info);
	void SetPosition(FVector2D Pos, FVector2D Alignment = { 0, 0 });
	
protected:
	FItemInfo ItemInfo;
	void SetImg(const FSlateBrush& Brush);
	void SetName(const FText& txt);
	void SetType(EType InType);
	void SetIntroduction(const FText& txt);
	void SetRarity(ERarity Rarity);

private:
	UPROPERTY(meta = (BindWidget))
	USizeBox* Block;

	UPROPERTY(meta = (BindWidget))
	UImage* BackGround;
	
	UPROPERTY(meta = (BindWidget))
	UImage* Img;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Name;
	
	UPROPERTY(meta = (BindWidget))
	UTextBlock* Type;

	UPROPERTY(meta = (BindWidget))
	UTextBlock* Introduction;
};
