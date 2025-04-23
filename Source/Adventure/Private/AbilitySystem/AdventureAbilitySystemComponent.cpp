// Copyright Choi JinWoo. All Rights Reserved.


#include "AbilitySystem/AdventureAbilitySystemComponent.h"

#include "AdventureGameplayTag.h"
#include "DebugHelper.h"
#include "AdventureType/AdventureStructTypes.h"

void UAdventureAbilitySystemComponent::OnAbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (!InInputTag.IsValid()) return;

	ABILITYLIST_SCOPE_LOCK();
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!AbilitySpec.DynamicAbilityTags.HasTagExact(InInputTag)) continue;

		if (InInputTag.MatchesTag(AdventureGameplayTags::InputTag_Toggleable) && AbilitySpec.IsActive())
		{
			CancelAbilityHandle(AbilitySpec.Handle);
		}
		else
		{
			TryActivateAbility(AbilitySpec.Handle);
		}

	}
	
}

void UAdventureAbilitySystemComponent::OnAbilityInputReleased(const FGameplayTag& InInputTag)
{
	
}

void UAdventureAbilitySystemComponent::InitializeAbilityFromCharacterInfo(const FPartyCharacterInfo& InCharacterInfo)
{
	if (FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecFromAbilityTag(AdventureGameplayTags::Ability_Player_ESkill))
	{
		AbilitySpec->Level = InCharacterInfo.ESkillLevel;
		MarkAbilitySpecDirty(*AbilitySpec);
	}
	if (FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecFromAbilityTag(AdventureGameplayTags::Ability_Player_RSkill))
	{
		AbilitySpec->Level = InCharacterInfo.RSkillLevel;
		MarkAbilitySpecDirty(*AbilitySpec);
	}
	if (FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecFromAbilityTag(AdventureGameplayTags::Ability_Player_Attack_Normal))
	{
		AbilitySpec->Level = InCharacterInfo.NormalAttackLevel;
		MarkAbilitySpecDirty(*AbilitySpec);
	}
	if (FGameplayAbilitySpec* AbilitySpec = GetAbilitySpecFromAbilityTag(AdventureGameplayTags::Ability_Player_Attack_Heavy))
	{
		AbilitySpec->Level = InCharacterInfo.NormalAttackLevel;
		MarkAbilitySpecDirty(*AbilitySpec);
	}
}

void UAdventureAbilitySystemComponent::ForEachAbility(const FForEachAbility& Delegate)
{
	FScopedAbilityListLock ActiveScopeLock(*this);
	for (const FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		if (!Delegate.ExecuteIfBound(AbilitySpec))
		{
			UE_LOG(LogTemp, Error, TEXT("Failed execute Delegate in %hs"), __FUNCTION__);
		}
	}
}

FGameplayAbilitySpec* UAdventureAbilitySystemComponent::GetAbilitySpecFromAbilityTag(const FGameplayTag& AbilityTag)
{
	ABILITYLIST_SCOPE_LOCK();
	
	for (FGameplayAbilitySpec& AbilitySpec : GetActivatableAbilities())
	{
		for (const FGameplayTag& Tag : AbilitySpec.Ability->AbilityTags)
		{
			if (Tag.MatchesTagExact(AbilityTag))
			{
				return &AbilitySpec;
			}
		}
	}
	return nullptr;
}
