// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AdventureGameplayAbility.h"
#include "AdventureType/AdventureStructTypes.h"
#include "AdventureDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureDamageGameplayAbility : public UAdventureGameplayAbility
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintPure)
	FDamageEffectParams MakeDamageEffectParams(AActor* TargetActor, FVector KnockBackDirectionOverride = FVector::ZeroVector) const;

protected:
	
	/* Damage */
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category="Damage", meta = (Categories = "Damage"))
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, Category="Damage", meta=(ClampMin="0.0"))
	FScalableFloat DamageMultiplier;
	
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float KnockBackForceMagnitude = 0.f;

	

};
