#pragma once

#include "CoreMinimal.h"
#include "CharacterAttribute.generated.h"

USTRUCT(BlueprintType)
struct FCharacterMainAttribute {
	GENERATED_BODY()

	/**
	 * Variables
	 */
	UPROPERTY(EditAnywhere) float CurHealth{ 10 };			// ��ǰ����
	UPROPERTY(EditAnywhere) int Level{ 1 };					// �ȼ�
	UPROPERTY(EditAnywhere) float CurExp{ 0 };				// ��ǰ����
	UPROPERTY(EditAnywhere) float ExpRequiredToLevelUp{ 5 };// �������辭��
	UPROPERTY(EditAnywhere) float Assets{ 0 };				// �Ƹ�ֵ
	UPROPERTY(EditAnywhere) float Unpicked{ 0 };			// δʰȡ

	UPROPERTY(EditAnywhere) float MaxHealth{ 10 };			// �������
	UPROPERTY(EditAnywhere) float HealthRecovery{ 0 };		// ��������
	UPROPERTY(EditAnywhere) float HealthStealRate{ 0 };		// %������ȡ
	UPROPERTY(EditAnywhere) float DamageRate{ 0 };			// %�˺�
	UPROPERTY(EditAnywhere) float MeleeDamage{ 0 };			// ��ս�˺�
	UPROPERTY(EditAnywhere) float RangedDamage{ 0 };		// Զ���˺�
	UPROPERTY(EditAnywhere) float ElementalDamage{ 0 };		// Ԫ���˺�
	UPROPERTY(EditAnywhere) float AttackSpeedRate{ 0 };		// %�����ٶ�
	UPROPERTY(EditAnywhere) float CriticalRate{ 0 };		// %������
	UPROPERTY(EditAnywhere) float Engineering{ 0 };			// ����ѧ
	UPROPERTY(EditAnywhere) float AttackRange{ 0 };			// ��Χ
	UPROPERTY(EditAnywhere) float Armor{ 0 };				// ����
	UPROPERTY(EditAnywhere) float DodgeRate{ 0 };			// %����	
	UPROPERTY(EditAnywhere) float Speed{ 0 } ;				// �ٶ�
	UPROPERTY(EditAnywhere) float Luck{ 0 };				// ����
	UPROPERTY(EditAnywhere) float Acquisition{ 0 };			// �ջ�

	UPROPERTY(EditAnywhere) float MaxNumofWeapons{ 6 };		// �����������
	UPROPERTY(EditAnywhere) float PickUpRadius{ 1500 };		// ʰȡ�뾶

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
