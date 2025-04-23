// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AdventureAbilitySystemComponent.generated.h"

struct FPartyCharacterInfo;
DECLARE_DELEGATE_OneParam(FForEachAbility, const FGameplayAbilitySpec&);

/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureAbilitySystemComponent : public UAbilitySystemComponent
{
	GENERATED_BODY()

public:
	void OnAbilityInputPressed(const FGameplayTag& InInputTag);
	void OnAbilityInputReleased(const FGameplayTag& InInputTag);
	void InitializeAbilityFromCharacterInfo(const FPartyCharacterInfo& InCharacterInfo);

	void ForEachAbility(const FForEachAbility& Delegate);
	
private:
	FGameplayAbilitySpec* GetAbilitySpecFromAbilityTag(const FGameplayTag& AbilityTag);
};
