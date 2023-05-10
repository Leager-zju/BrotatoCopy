#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Commons/CharacterAttribute.h"
#include "Commons/ItemInfo.h"
#include "Character_Base.generated.h"

class ACombatInterfaceHUD;
class ACombatLevel;
class AWeapon_Base;
class UCameraComponent;
class UMyGameInstance;
class UPaperFlipbook;
class USphereComponent;
class USpringArmComponent;

USTRUCT(BlueprintType)
struct FPropInfo {
	GENERATED_USTRUCT_BODY()

public:
	FPropInfo() = default;
	FPropInfo(UClass* PropClass_, int Count_, ERarity Rarity_): PropClass(PropClass_), Count(Count_), Rarity(Rarity_) {}
	
	UPROPERTY(VisibleAnywhere) UClass* PropClass = nullptr;
	UPROPERTY(VisibleAnywhere) int Count;
	UPROPERTY(VisibleAnywhere) ERarity Rarity;
};

USTRUCT(BlueprintType)
struct FWeaponInfo {
	GENERATED_USTRUCT_BODY()

public:
	FWeaponInfo() = default;
	FWeaponInfo(UClass* WeaponClass_, ERarity Rarity_): WeaponClass(WeaponClass_), Rarity(Rarity_) {}

	UPROPERTY(VisibleAnywhere) UClass* WeaponClass = nullptr;
	UPROPERTY(VisibleAnywhere) ERarity Rarity;

	bool operator==(const FWeaponInfo& other) const {
		return WeaponClass == other.WeaponClass && Rarity == other.Rarity;
	}
};

UCLASS()
class BROTATOCOPY_API ACharacter_Base : public APaperCharacter
{
	GENERATED_BODY()

public:
	ACharacter_Base();
	void Initial();
	void SetWeaponClassAtIndex(int index, const FWeaponInfo& NewWeapon);
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
	virtual void BeginNewRound();
	virtual void LevelUp();

	void RecycleUnpickup(float Unpicked);

	void TakeCost(int Cost);
	void BuyProp(const FPropInfo& NewProp, int Cost);
	void BuyWeapon(const FWeaponInfo& NewWeapon, int Cost);
	int CompositeWeapon(int WeaponIndex);
	void SellWeapon(int WeaponIndex, int Price);
	void RemoveWeapon(int WeaponIndex);
	void UpdateCombatInterfaceWidget();

	void SetCombatLevel(ACombatLevel* Level) { CombatLevel = Level; }
	FCharacterMainAttribute& GetMainAttribute() { return MainAttribute; }
	FCharacterSecondaryAttribute& GetSecondaryAttribute() { return SecondaryAttribute; }
	TArray<FWeaponInfo>& GetWeaponOwned() { return WeaponsOwned; }
	TArray<FPropInfo>& GetPropsOwned() { return PropsOwned; }
	FItemInfo& GetInfo() { return CharacterInfo; }
	void EnableMove() { bInCombat = true; }
	void DisableMove() { bInCombat = false; }

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds);

	int CompositeWeapon(int WeaponIndex, const FWeaponInfo& WeaponOwned);

	/**
	 * Combat
	 */
	virtual void TryAttack();
	void ReEquipWeapon();
	virtual void Attack(int Weapon_Index, AActor* Target);
	virtual void Dodge();
	virtual void Die();
	void PickupAssets(float Assets, float Exp);

	/**
	 * Inputs
	 */
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent);
	void MoveRight(float Value);
	void MoveUp(float Value);
	bool bInCombat{true};

	/**
	 * Overlap
	 */
	UFUNCTION()
	virtual void Pickup(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

	UFUNCTION()
	virtual void Streamin(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

protected:
	UPROPERTY(EditDefaultsOnly)
	FCharacterMainAttribute MainAttribute {};

	UPROPERTY(EditDefaultsOnly)
	FCharacterSecondaryAttribute SecondaryAttribute {};

	UPROPERTY(EditDefaultsOnly)
	FItemInfo CharacterInfo {};
		
	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	UPaperFlipbook* Idle;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	UPaperFlipbook* Run;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	UPaperFlipbook* Dead;

	UPROPERTY(VisibleAnywhere, Category = View)
	USpringArmComponent* SpringArm;

	UPROPERTY(VisibleAnywhere, Category = View)
	UCameraComponent* Camera;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	USphereComponent* PickUpSphere;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	USphereComponent* StreaminSphere;

	UPROPERTY(EditDefaultsOnly, Category = Combat)
	TArray<USceneComponent*> Weapons_Position;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	TArray<FWeaponInfo> WeaponsOwned;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	TArray<AWeapon_Base*> Weapons;

	UPROPERTY(VisibleAnywhere, Category = Combat)
	TArray<FPropInfo> PropsOwned;

	TMap<UClass*, int> PropClass2Index;


	/**
	 * Upper layer
	 */
	UPROPERTY(VisibleAnywhere)
	APlayerController* PC;
	
	UPROPERTY(VisibleAnywhere)
	ACombatInterfaceHUD* CombatHUD;

	UPROPERTY(VisibleAnywhere)
	UMyGameInstance* MyGameIns;

	UPROPERTY(VisibleAnywhere)
	ACombatLevel* CombatLevel;
};	
