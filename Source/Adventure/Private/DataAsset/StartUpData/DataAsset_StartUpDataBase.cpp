// Copyright Choi JinWoo. All Rights Reserved.


#include "DataAsset/StartUpData/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/AdventureAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/AdventureGameplayAbility.h"


void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UAdventureAbilitySystemComponent* InASC, int32 ApplyLevel)
{
	check(InASC);

	GrantAbilities(ActivateOnGivenAbilities, InASC, ApplyLevel);
	GrantAbilities(ReactiveAbilities, InASC, ApplyLevel);

	if (!StartUpAbilityInfo.IsEmpty())
	{
		for (const FAdventureAbilityInfo& AbilityInfo : StartUpAbilityInfo)
		{
			if (!AbilityInfo.AbilityToGrant) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityInfo.AbilityToGrant);
			AbilitySpec.Level = ApplyLevel;
			AbilitySpec.SourceObject = InASC->GetAvatarActor();

			if (AbilityInfo.InputTag.IsValid())
			{
				AbilitySpec.DynamicAbilityTags.AddTag(AbilityInfo.InputTag);
			}

			InASC->GiveAbility(AbilitySpec);
		}
		
	}
	

	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& EffectClass : StartUpGameplayEffects)
		{
			if (!EffectClass) continue;

			FGameplayEffectContextHandle EffectContextHandle = InASC->MakeEffectContext();
			FGameplayEffectSpecHandle EffectSpecHandle = InASC->MakeOutgoingSpec(EffectClass, ApplyLevel, EffectContextHandle);
			InASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
			
		}
	}

	
	
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UAdventureGameplayAbility>>& InAbilityToGive, UAdventureAbilitySystemComponent* InASC, int32 ApplyLevel)
{
	if (InAbilityToGive.IsEmpty()) return;

	for (const TSubclassOf<UAdventureGameplayAbility>& Ability : InAbilityToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASC->GetAvatarActor();
		AbilitySpec.Level = ApplyLevel;
		
		InASC->GiveAbility(AbilitySpec);
	}
	
	
}
