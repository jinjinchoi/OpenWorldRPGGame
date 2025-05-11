// Copyright Choi JinWoo. All Rights Reserved.


#include "DataAsset/StartUpData/DataAsset_StartUpDataBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AdventureGameplayTag.h"
#include "AbilitySystem/AdventureAbilitySystemComponent.h"
#include "AbilitySystem/AdventureAttributeSet.h"
#include "AbilitySystem/Abilities/AdventureGameplayAbility.h"


void UDataAsset_StartUpDataBase::GrantCharacterLevelEffect(UAdventureAbilitySystemComponent* InASC, const int32 LevelToApply) const
{
	check(LevelGameplayEffect);
	
	FGameplayEffectContextHandle EffectContextHandle = InASC->MakeEffectContext();
	FGameplayEffectSpecHandle EffectSpecHandle = InASC->MakeOutgoingSpec(LevelGameplayEffect, 1.f, EffectContextHandle);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(EffectSpecHandle, AdventureGameplayTags::Attribute_Player_CharacterLevel, LevelToApply);
	InASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
}

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

	const UAdventureAttributeSet* AdventureAttributeSet = Cast<UAdventureAttributeSet>(InASC->GetAttributeSet(UAdventureAttributeSet::StaticClass()));
	check(AdventureAttributeSet);
	const int32 CharacterLevel = AdventureAttributeSet->GetCharacterLevel();
	
	if (!StartUpGameplayEffects.IsEmpty())
	{
		for (const TSubclassOf<UGameplayEffect>& EffectClass : StartUpGameplayEffects)
		{
			if (!EffectClass) continue;

			FGameplayEffectContextHandle EffectContextHandle = InASC->MakeEffectContext();
			FGameplayEffectSpecHandle EffectSpecHandle = InASC->MakeOutgoingSpec(EffectClass, CharacterLevel, EffectContextHandle);
			InASC->ApplyGameplayEffectSpecToSelf(*EffectSpecHandle.Data.Get());
			
		}
	}
}
