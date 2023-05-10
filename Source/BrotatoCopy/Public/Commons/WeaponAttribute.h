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
	UPROPERTY(EditAnywhere) float BasicDamage{ 1 };			// �����˺�
	UPROPERTY(EditAnywhere) float BasicAttackRange{ 1000 };	// ����������Χ
	UPROPERTY(EditAnywhere) float BasicAttackSpeed;			// ���������ٶ�
	UPROPERTY(EditAnywhere) float MeleeMultiplier{ 0 };		// %��ս�˺��ӳ�
	UPROPERTY(EditAnywhere) float RangedMultiplier{ 0 };	// %Զ���˺��ӳ�
	UPROPERTY(EditAnywhere) float ElementalMultiplier{ 0 };	// %Ԫ���˺��ӳ�
	UPROPERTY(EditAnywhere) float EngneerMultiplier{ 0 };	// %����ѧ�ӳ�
	UPROPERTY(EditAnywhere) int Perforation{ 0 };			// ��ͨ����
	UPROPERTY(EditAnywhere) int BasicCriticalRate{ 0 };		// %����������
	UPROPERTY(EditAnywhere) float CriticalMutiplier{ 1.5 };	// �����˺�����

	/**
	 * Functions
	 */
	float CalculateAttackRange(const FCharacterMainAttribute& Attribute);
	float CalculateDamage(const FCharacterMainAttribute& Attribute);
	float CalculateCriticalRate(const FCharacterMainAttribute& Attribute);
};
