#pragma once

#include "CoreMinimal.h"
#include "EnemyAttribute.generated.h"

USTRUCT(BlueprintType)
struct FEnemyAttribute {
	GENERATED_BODY()

	UPROPERTY(EditAnywhere) float CurHealth{ 1 };			// ��ǰ����
	UPROPERTY(EditAnywhere) float MaxHealth{ 1 };			// �������
	UPROPERTY(EditAnyWhere) float Damage{ 1 };				// �˺�
	UPROPERTY(EditAnywhere) float AttackSpeedRate{ 0 };		// %�����ٶ�
	UPROPERTY(EditAnywhere) float AttackRange{ 1 };			// ��Χ

	UPROPERTY(EditAnyWhere) int AssetsGenerated{ 1 };		// ����Ƹ�ֵ
	UPROPERTY(EditAnyWhere)	int ExpGenerated{ 1 };			// ���侭��ֵ

	/**
	 * Functions
	 */
	void ReceiveDamage(float Value);
	bool Alive();
};