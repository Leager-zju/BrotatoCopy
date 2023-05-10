#include "Weapons/Bullet_Base.h"

#include "Enemies/Enemy_Base.h"

#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "PaperSpriteComponent.h"

ABullet_Base::ABullet_Base()
{
	Projectile = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));

	GetRenderComponent()->SetCollisionResponseToAllChannels(ECR_Ignore);
	GetRenderComponent()->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);

	// 保证直线运动
	Projectile->ProjectileGravityScale = 0;
	Projectile->bConstrainToPlane = true;
	Projectile->SetPlaneConstraintNormal(FVector::ZAxisVector);

	Speed = Projectile->GetMaxSpeed();

	// WorldDynamic 类型，仅与 Pawn 类型产生重叠事件
	BulletCollision = CreateDefaultSubobject<USphereComponent>(TEXT(" Collision"));
	BulletCollision->SetupAttachment(GetRootComponent());
	BulletCollision->SetGenerateOverlapEvents(true);
	BulletCollision->SetCollisionObjectType(ECC_WorldDynamic);
	BulletCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	BulletCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
}

void ABullet_Base::BeginPlay()
{
	Super::BeginPlay();
	BulletCollision->OnComponentBeginOverlap.AddDynamic(this, &ABullet_Base::BulletHitEvent);
}

void ABullet_Base::BulletHitEvent(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (GetInstigator() && GetOwner() && OtherActor && Cast<AEnemy_Base>(OtherActor)) {
		UGameplayStatics::ApplyDamage(OtherActor, BulletDamage, GetInstigator()->GetController(), GetOwner(), UDamageType::StaticClass());
		Destroy();
	}
}
