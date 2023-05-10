#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Commons/ItemInfo.h"
#include "Commons/WeaponAttribute.h"
#include "Weapon_Base.generated.h"

class ACharacter_Base;
class UArrowComponent;
class UPaperSprite;

UCLASS()
class BROTATOCOPY_API AWeapon_Base : public APaperSpriteActor
{
	GENERATED_BODY()

public:
	AWeapon_Base();
	void SetPlayer(ACharacter_Base* p);
	virtual void Attack(FCharacterMainAttribute& CharacterAttribute);
	bool CanAttack(AActor*& Target, FCharacterMainAttribute& CharacterAttribute);
	
	FORCEINLINE	void SetRarity(ERarity Rarity) { WeaponInfo.Rarity = Rarity; }
	FItemInfo& GetInfo(ERarity Rarity);
	FItemInfo& GetInfoWithWhiteRarity();
	FItemInfo& GetInfoWithBlueRarity();
	FItemInfo& GetInfoWithPurpleRarity();
	FItemInfo& GetInfoWithRedRarity();

protected:
	UPROPERTY(EditDefaultsOnly)
	UClass* BulletClass;

	UPROPERTY(EditDefaultsOnly)
	FItemInfo WeaponInfo {};

	UPROPERTY(EditDefaultsOnly)
	UArrowComponent* Arrow;

	UPROPERTY(VisibleAnywhere)
	ACharacter_Base* Player;

	UPROPERTY(EditDefaultsOnly)
	FWeaponAttribute WeaponAttribute;
	
	UPROPERTY(VisibleAnywhere)
	AActor* AttackTarget;

	UPROPERTY(VisibleAnywhere)
	TArray<AActor*> ActorsToIgnore;

	FTimerHandle AttackTimer;

	UPROPERTY(VisibleAnywhere)
	float AttackInterval{ 1 };

	UPROPERTY(VisibleAnywhere)
	bool bCanAttack{ true };

	UPROPERTY(VisibleAnywhere)
	FString WeaponName = TEXT("法杖");

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds);
	void AttackTimeOut() { bCanAttack = true; }
};
