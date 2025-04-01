// Copyright Choi JinWoo. All Rights Reserved.


#include "AbilitySystem/AdventureAbilitySystemGlobals.h"

#include "AdventureType/AdventureAbilityTypes.h"

FGameplayEffectContext* UAdventureAbilitySystemGlobals::AllocGameplayEffectContext() const
{
	return new FAdventureGameplayEffectContext();
}
