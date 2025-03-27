// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "AdventureGameplayAbility.generated.h"

UENUM(BlueprintType)
enum class EAdventureAbilityActivationPolicy : uint8
{
	OnTriggered,
	OnGiven
};

/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:
	/* Begin UGameplayAbility */
	virtual void OnGiveAbility(const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilitySpec& Spec) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	/* End UGameplayAbility  */
	
	UPROPERTY(EditDefaultsOnly, Category="AdventureAbility")
	EAdventureAbilityActivationPolicy AbilityActivationPolicy = EAdventureAbilityActivationPolicy::OnTriggered;
	
};
