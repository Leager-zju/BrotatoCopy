#include "Commons/EnemyAttribute.h"

void FEnemyAttribute::ReceiveDamage(float Value)
{
	CurHealth -= Value;
	if (CurHealth < 0) {
		CurHealth = 0;
	}
}

bool FEnemyAttribute::Alive()
{
	return CurHealth > 0;
}
