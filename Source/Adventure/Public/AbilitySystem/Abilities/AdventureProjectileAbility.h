// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AdventureDamageGameplayAbility.h"
#include "AdventureProjectileAbility.generated.h"

class AAdventureProjectileBase;
/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureProjectileAbility : public UAdventureDamageGameplayAbility
{
	GENERATED_BODY()

protected:
	UFUNCTION(BlueprintCallable, Category = "Projectile Ability")
	void SpawnProjectile(const FVector& SpawnLocation, const FVector& TargetLocation);
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Propertires");
	TSubclassOf<AAdventureProjectileBase> ProjectileClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Projectile Propertires");
	float ProjectileSpeed = 400.f;

	
};
