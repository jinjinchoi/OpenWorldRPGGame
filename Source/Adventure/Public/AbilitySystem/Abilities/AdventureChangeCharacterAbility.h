// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AdventureGameplayAbility.h"
#include "AdventureChangeCharacterAbility.generated.h"

class UControllableCharacterManager;
/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureChangeCharacterAbility : public UAdventureGameplayAbility
{
	GENERATED_BODY()

public:
	/* Begin UGameplayAbility Interface */
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	/* End UGameplayAbility Interface */

protected:
	UFUNCTION(BlueprintCallable, Category="Character Management")
	void OnCharacterChangeAbilityActivated();
	
	UFUNCTION(BlueprintCallable, Category="Character Management")
	void SpawnNewCharacterAndRemoveOldCharacter(int32 InCharacterIndex);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UControllableCharacterManager> CharacterManager;
	
};
