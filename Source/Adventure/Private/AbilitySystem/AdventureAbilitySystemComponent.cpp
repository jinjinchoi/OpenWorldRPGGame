// Copyright Choi JinWoo. All Rights Reserved.


#include "AbilitySystem/AdventureAbilitySystemComponent.h"

#include "DebugHelper.h"

void UAdventureAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;

	FScopedAbilityListLock AbilityListLock(*this);
	
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;

		TryActivateAbility(AbilitySpec.Handle);
		
	}
	
}

void UAdventureAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	
}
