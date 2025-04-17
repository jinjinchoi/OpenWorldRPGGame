// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AdventureProjectileBase.h"
#include "GameFramework/Actor.h"
#include "AdventureMultiHitProjectile.generated.h"

class UNiagaraSystem;

UCLASS()
class ADVENTURE_API AAdventureMultiHitProjectile : public AAdventureProjectileBase
{
	GENERATED_BODY()

protected:
	virtual void BeginPlay() override;
	
	/* Begin Adventure Projectile Base */
	virtual void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	virtual void OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;
	/* End Adventure Projectile Base */

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Properties")
	TObjectPtr<USoundBase> HitSound;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Properties")
	float DamageInterval = 0.5f;

private:
	UPROPERTY()
	TArray<AActor*> OverlappingActors;

	FTimerHandle OverlappingTimer;

	void ApplyDamageEffectToOverlappedActors();
	
};
