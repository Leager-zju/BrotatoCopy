#pragma once

#include "CoreMinimal.h"
#include "PaperCharacter.h"
#include "Commons/EnemyAttribute.h"
#include "Commons/ItemInfo.h"
#include "Enemy_Base.generated.h"

class AAIController;
class ACharacter_Base;
class AItem_Base;
class UPaperFlipbook;

UCLASS()
class BROTATOCOPY_API AEnemy_Base : public APaperCharacter
{
	GENERATED_BODY()
public:
	AEnemy_Base();
	virtual float TakeDamage(float Damage, struct FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser);
	FItemInfo& GetInfo() { return EnemyInfo; }

protected:
	virtual void BeginPlay();
	virtual void Tick(float DeltaSeconds);
	
	/**
	 * 战斗
	 */
	bool CanAttack();
	virtual void Attack();
	void AttackTimeOut() { bCanAttack = true; };
	virtual void MoveTo(AActor* Target);
	virtual void Die();

protected:
	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	UPaperFlipbook* Walk;

	UPROPERTY(EditDefaultsOnly, Category = Sprite)
	UPaperFlipbook* Dead;

	UPROPERTY(EditDefaultsOnly)
	FEnemyAttribute EnemyAttribute;

	UPROPERTY(EditDefaultsOnly)
	FItemInfo EnemyInfo {};

	/**
	 * 战斗
	 */
	FTimerHandle AttackTimer;

	float AttackInterval{ 1 };

	UPROPERTY(VisibleAnywhere)
	bool bCanAttack{ true };

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AItem_Base> DropItemClass;

	/**
	 * 导航相关
	 */
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<AActor> AttackTargetClass;

	UPROPERTY(VisibleAnywhere)
	ACharacter_Base* AttackTarget { nullptr };

	UPROPERTY(VisibleAnywhere)
	AAIController* EnemyController;
};
