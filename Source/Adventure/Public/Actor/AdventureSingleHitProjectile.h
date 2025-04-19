// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Actor/AdventureProjectileBase.h"
#include "AdventureSingleHitProjectile.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventureSingleHitProjectile : public AAdventureProjectileBase
{
	GENERATED_BODY()

protected:
	/* Begin Adventure Projectile Base */
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	/* End Adventure Projectile Base */

	virtual void Destroyed() override;

private:
	bool bIsHit = false;
};
