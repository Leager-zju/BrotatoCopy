// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "PaperSpriteActor.h"
#include "Bullet_Base.generated.h"

class UProjectileMovementComponent;
class USphereComponent;

UCLASS()
class BROTATOCOPY_API ABullet_Base : public APaperSpriteActor
{
	GENERATED_BODY()
public:
	ABullet_Base();
	
	float GetSpeed() { return Speed; }
	void SetDamage(float Damage) { BulletDamage = Damage; }
	void SetPerforation(int Value) { Perforation = Value; }
	void SetRebound(int Value) { Rebound = Value; }

protected:
	UPROPERTY(EditDefaultsOnly)
	UProjectileMovementComponent* Projectile;

	UPROPERTY(VisibleAnywhere)
	USphereComponent* BulletCollision;

	UPROPERTY(VisibleAnywhere)
	float Speed;

	UPROPERTY(VisibleAnywhere)
	float BulletDamage{ 1 };

	UPROPERTY(VisibleAnywhere)
	int Perforation{ 0 };	// 贯通次数

	UPROPERTY(VisibleAnywhere)
	int Rebound{ 0 };		// 反弹次数

protected:
	virtual void BeginPlay();

	UFUNCTION()
	void BulletHitEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
};
