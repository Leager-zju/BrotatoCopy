#pragma once

#include "CoreMinimal.h"
#include "WeaponAttribute.generated.h"

struct FCharacterMainAttribute;

USTRUCT(BlueprintType)
struct FWeaponAttribute {
	GENERATED_BODY()

	/**
	 * Variables
	 */
	UPROPERTY(EditAnywhere) float BasicDamage{ 1 };			// 基础伤害
	UPROPERTY(EditAnywhere) float BasicAttackRange{ 1000 };	// 基础攻击范围
	UPROPERTY(EditAnywhere) float BasicAttackSpeed;			// 基础攻击速度
	UPROPERTY(EditAnywhere) float MeleeMultiplier{ 0 };		// %近战伤害加成
	UPROPERTY(EditAnywhere) float RangedMultiplier{ 0 };	// %远程伤害加成
	UPROPERTY(EditAnywhere) float ElementalMultiplier{ 0 };	// %元素伤害加成
	UPROPERTY(EditAnywhere) float EngneerMultiplier{ 0 };	// %工程学加成
	UPROPERTY(EditAnywhere) int Perforation{ 0 };			// 贯通次数
	UPROPERTY(EditAnywhere) int BasicCriticalRate{ 0 };		// %基础暴击率
	UPROPERTY(EditAnywhere) float CriticalMutiplier{ 1.5 };	// 暴击伤害倍数

	/**
	 * Functions
	 */
	float CalculateAttackRange(const FCharacterMainAttribute& Attribute);
	float CalculateDamage(const FCharacterMainAttribute& Attribute);
	float CalculateCriticalRate(const FCharacterMainAttribute& Attribute);
};
