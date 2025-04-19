// Copyright Choi JinWoo. All Rights Reserved.


#include "Actor/AdventureSingleHitProjectile.h"
#include "Interface/CombatInterface.h"

void AAdventureSingleHitProjectile::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                         UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValidOverlap(OtherActor))
	{
		if (ICombatInterface::Execute_IsDead(OtherActor))
		{
			return;
		}

		ApplyGameplayEffectToTargetActor(OtherActor);
	}

	bIsHit = true;
	OnHit();
	Destroy();
	
}

void AAdventureSingleHitProjectile::Destroyed()
{
	Super::Destroyed();

	if (!bIsHit)
	{
		OnHit();
	}
}
