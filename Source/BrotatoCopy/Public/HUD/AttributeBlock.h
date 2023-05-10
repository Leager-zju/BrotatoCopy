#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "AttributeBlock.generated.h"

class ACharacter_Base;
struct FCharacterMainAttribute;
struct FCharacterSecondaryAttribute;
class UButton;
class USizeBox;
class UMainAttributeTextBlock;

UCLASS()
class BROTATOCOPY_API UAttributeBlock : public UUserWidget
{
	GENERATED_BODY()
public:
	virtual void NativeConstruct();
	void UpdateAttr(FCharacterMainAttribute& MainAttr, FCharacterSecondaryAttribute& SecondaryAttr);
	void UpdateMainAttr(FCharacterMainAttribute& MainAttr);
	void UpdateSecondaryAttr(FCharacterSecondaryAttribute& SecondaryAttr);

	UFUNCTION()
	void SwitchToMain();

	UFUNCTION()
	void SwitchToSecondary();

private:
	UPROPERTY(meta = (BindWidget))
	UButton* Main;

	UPROPERTY(meta = (BindWidget))
	UButton* Secondary;

	UPROPERTY(meta = (BindWidget))
	USizeBox* ShowBox;

	UPROPERTY(EditAnywhere)
	TSubclassOf<UMainAttributeTextBlock> MainAttributeTextBlockClass;
	
	UMainAttributeTextBlock* MainAttributeTextBlock;
	//TSubclassOf<class USecondaryAttributeTextBlock> SecondaryAttributeTextBlockClass;

	bool bIsMain{ true };	// 当前显示主要属性
};
