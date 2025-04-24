// Copyright Choi JinWoo. All Rights Reserved.


#include "DataAsset/StartUpData/DataAsset_StartUpDataBase.h"
#include "AbilitySystem/AdventureAbilitySystemComponent.h"
#include "AbilitySystem/Abilities/AdventureGameplayAbility.h"


void UDataAsset_StartUpDataBase::GiveToAbilitySystemComponent(UAdventureAbilitySystemComponent* InASC)
{
	check(InASC);

	GrantAbilities(ActivateOnGivenAbilities, InASC);
	GrantAbilities(ReactiveAbilities, InASC);

	if (!StartUpAbilityInfo.IsEmpty())
	{
		for (const FAdventureAbilityInfo& AbilityInfo : StartUpAbilityInfo)
		{
			if (!AbilityInfo.AbilityToGrant) continue;

			FGameplayAbilitySpec AbilitySpec(AbilityInfo.AbilityToGrant);
			AbilitySpec.Level = 1.f;
			AbilitySpec.SourceObject = InASC->GetAvatarActor();

			if (AbilityInfo.InputTag.IsValid())
			{
				AbilitySpec.DynamicAbilityTags.AddTag(AbilityInfo.InputTag);
			}

			InASC->GiveAbility(AbilitySpec);
		}
	}
	
}

void UDataAsset_StartUpDataBase::GrantAbilities(const TArray<TSubclassOf<UAdventureGameplayAbility>>& InAbilityToGive, UAdventureAbilitySystemComponent* InASC)
{
	if (InAbilityToGive.IsEmpty()) return;

	for (const TSubclassOf<UAdventureGameplayAbility>& Ability : InAbilityToGive)
	{
		if (!Ability) continue;

		FGameplayAbilitySpec AbilitySpec(Ability);
		AbilitySpec.SourceObject = InASC->GetAvatarActor();
		AbilitySpec.Level = 1.f;
		
		InASC->GiveAbility(AbilitySpec);
	}
	
	
}

void UDataAsset_StartUpDataBase::GrantStartUpGameplayEffect(UAdventureAbilitySystemComponent* InASC)
{
	check(InASC);
	
	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& EffectClass : StartUpGameplayEffects)
		{
			if (!EffectClass) continue;

			FGameplayEffectContextHandle EffectContextHandle = InASC->MakeEffectContext();
			FGameplayEffectSpecHandle EffectSpecHandle = InASC->MakeOutgoingSpec(EffectClass, 1.f, EffectContextHandle);
			InASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
			
		}
	}
}
