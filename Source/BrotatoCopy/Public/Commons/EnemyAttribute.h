#pragma once

#include "CoreMinimal.h"
#include "EnemyAttribute.generated.h"

USTRUCT(BlueprintType)
struct FEnemyAttribute {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) float CurHealth{ 1 };			// 当前生命
	UPROPERTY(EditAnywhere) float MaxHealth{ 1 };			// 最大生命
	UPROPERTY(EditAnyWhere) float Damage{ 1 };				// 伤害
	UPROPERTY(EditAnywhere) float AttackSpeedRate{ 0 };		// %攻击速度
	UPROPERTY(EditAnywhere) float AttackRange{ 1 };			// 范围

	UPROPERTY(EditAnyWhere) int AssetsGenerated{ 1 };		// 掉落财富值
	UPROPERTY(EditAnyWhere)	int ExpGenerated{ 1 };			// 掉落经验值

	/**
	 * Functions
	 */
	void ReceiveDamage(float Value);
	bool Alive();
};