#pragma once

#include "CoreMinimal.h"
#include "CharacterAttribute.generated.h"

USTRUCT(BlueprintType)
struct FCharacterMainAttribute {
	GENERATED_BODY()

	/**
	 * Variables
	 */
	UPROPERTY(EditAnywhere) float CurHealth{ 10 };			// 当前生命
	UPROPERTY(EditAnywhere) int Level{ 1 };					// 等级
	UPROPERTY(EditAnywhere) float CurExp{ 0 };				// 当前经验
	UPROPERTY(EditAnywhere) float ExpRequiredToLevelUp{ 5 };// 升级所需经验
	UPROPERTY(EditAnywhere) float Assets{ 0 };				// 财富值
	UPROPERTY(EditAnywhere) float Unpicked{ 0 };			// 未拾取

	UPROPERTY(EditAnywhere) float MaxHealth{ 10 };			// 最大生命
	UPROPERTY(EditAnywhere) float HealthRecovery{ 0 };		// 生命再生
	UPROPERTY(EditAnywhere) float HealthStealRate{ 0 };		// %生命窃取
	UPROPERTY(EditAnywhere) float DamageRate{ 0 };			// %伤害
	UPROPERTY(EditAnywhere) float MeleeDamage{ 0 };			// 近战伤害
	UPROPERTY(EditAnywhere) float RangedDamage{ 0 };		// 远程伤害
	UPROPERTY(EditAnywhere) float ElementalDamage{ 0 };		// 元素伤害
	UPROPERTY(EditAnywhere) float AttackSpeedRate{ 0 };		// %攻击速度
	UPROPERTY(EditAnywhere) float CriticalRate{ 0 };		// %暴击率
	UPROPERTY(EditAnywhere) float Engineering{ 0 };			// 工程学
	UPROPERTY(EditAnywhere) float AttackRange{ 0 };			// 范围
	UPROPERTY(EditAnywhere) float Armor{ 0 };				// 护甲
	UPROPERTY(EditAnywhere) float DodgeRate{ 0 };			// %闪避	
	UPROPERTY(EditAnywhere) float Speed{ 0 } ;				// 速度
	UPROPERTY(EditAnywhere) float Luck{ 0 };				// 幸运
	UPROPERTY(EditAnywhere) float Acquisition{ 0 };			// 收获

	UPROPERTY(EditAnywhere) float MaxNumofWeapons{ 6 };		// 最大武器数量
	UPROPERTY(EditAnywhere) float PickUpRadius{ 1500 };		// 拾取半径

	/**
	 * Functions
	 */
	void SetOwner(ACharacter_Base* NewOwner);
	float GetHealthPercent();
	float GetExpPercent();
	void IncreaseAssets(float Value);
	void IncreaseUnpicked(float Value);
	void IncreaseExp(float Value);
	void LevelUp();
	void ReceiveDamage(float Damage);
	bool Alive();

private:
	class ACharacter_Base* Owner;
};

USTRUCT(BlueprintType)
struct FCharacterSecondaryAttribute {
	GENERATED_BODY()
};
