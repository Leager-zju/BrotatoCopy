#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "MyGameInstance.generated.h"

UCLASS()
class BROTATOCOPY_API UMyGameInstance : public UGameInstance
{
	GENERATED_BODY()
public:
	TArray<UClass*>& GetCharacterClasses() { return CharacterClasses; }
	TArray<UClass*>& GetPropClasses() { return PropClasses; }
	TArray<UClass*>& GetWeaponOwned() { return WeaponsOwned; }
	TArray<UClass*>& GetStrengthenClasses() { return StrengthenClasses; }

	UClass* GetSelectedCharacterClass() { return SelectedCharacterClass; }
	void SetSelectedCharacterClass(UClass* CharacterClass) { SelectedCharacterClass = CharacterClass; }

	UClass* GetSelectedWeaponClass() { return SelectedWeaponClass; }
	void SetSelectedWeaponClass(UClass* WeaponClass) { SelectedWeaponClass = WeaponClass; }

	UClass* RandomWeaponPropClass();
	UClass* RandomStrengthenClass();

private:
	UPROPERTY(EditAnywhere)
	TArray<UClass*> CharacterClasses;

	UPROPERTY(EditAnywhere)
	TArray<UClass*> PropClasses;

	UPROPERTY(EditAnywhere)
	TArray<UClass*> WeaponsOwned;

	UPROPERTY(EditAnywhere)
	TArray<UClass*> StrengthenClasses;

	UPROPERTY(VisibleAnywhere)
	UClass* SelectedCharacterClass; // 初始选中的角色类

	UPROPERTY(VisibleAnywhere)
	UClass* SelectedWeaponClass;	// 初始选中的武器类
};
