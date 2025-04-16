// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AdventureType/AdventureStructTypes.h"
#include "GameFramework/Actor.h"
#include "AdventureProjectileBase.generated.h"

class UProjectileMovementComponent;
class USphereComponent;
class UNiagaraSystem;

UCLASS()
class ADVENTURE_API AAdventureProjectileBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AAdventureProjectileBase();

	UPROPERTY()
	FDamageEffectParams DamageEffectParams;

protected:
	virtual void BeginPlay() override;
	
	UFUNCTION()
	void OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(VisibleAnywhere)
	TObjectPtr<UProjectileMovementComponent> ProjectileMovement;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Properties")
	float LifeSpan = 10.f;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Properties")
	TObjectPtr<UNiagaraSystem> ImpactEffect;

	UPROPERTY(EditDefaultsOnly, Category = "Projectile Properties")
	TObjectPtr<USoundBase> ImpactSound;

private:
	bool IsValidOverlap(AActor* OtherActor) const;

public:
	FORCEINLINE UProjectileMovementComponent* GetProjectileMovementComponent() const { return ProjectileMovement; }
	
};
