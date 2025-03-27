// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AdventureGameplayAbility.h"
#include "AdventureDamageGameplayAbility.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureDamageGameplayAbility : public UAdventureGameplayAbility
{
	GENERATED_BODY()

protected:
	
	/* Damage */
	
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UGameplayEffect> DamageEffectClass;

	UPROPERTY(EditDefaultsOnly, Category="Damage", meta = (Categories = "Damage"))
	FGameplayTag DamageType;

	UPROPERTY(EditDefaultsOnly, Category="Damage", meta=(ClampMin="0.0"))
	FScalableFloat DamageMultiplier ;
	
	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float KnockBackChance = 0.f;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	FVector KnockBackDirection = FVector::ZeroVector;

	UPROPERTY(EditDefaultsOnly, Category="Damage")
	float KnockBackForceMagnitude = 1000.f;

	
	/* CoolDown */
	
	virtual FGameplayTagContainer* GetCooldownTags() const override;
	virtual void ApplyCooldown(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo) const override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Cooldown, meta=(Categories = "Cooldown"))
	FGameplayTagContainer CooldownTags;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Cooldown)
	FScalableFloat CooldownDuration;

	UPROPERTY(Transient)
	FGameplayTagContainer TempCooldownTags;
};
