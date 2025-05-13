// Copyright Choi JinWoo. All Rights Reserved.


#include "DataAsset/StartUpData/DataAsset_StartUpData_Player.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AdventureGameplayTag.h"
#include "AbilitySystem/AdventureAbilitySystemComponent.h"
#include "AdventureType/AdventureStructTypes.h"

void UDataAsset_StartUpData_Player::ApplySetByCallerEffectByCharacterInfo(UAdventureAbilitySystemComponent* InASC, const FPartyCharacterInfo& InCharacterInfo) const
{
	check(InASC && InCharacterInfo.IsValid() && SetByCallerGameplayEffect);

	FGameplayEffectContextHandle ContextHandle = InASC->MakeEffectContext();
	ContextHandle.AddSourceObject(InASC->GetAvatarActor());

	const FGameplayEffectSpecHandle SpecHandle = InASC->MakeOutgoingSpec(SetByCallerGameplayEffect, 1.f, ContextHandle);
	
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, AdventureGameplayTags::Attribute_Player_CurrentHealth, InCharacterInfo.CurrentHealth);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, AdventureGameplayTags::Attribute_Player_CurrentStamina, InCharacterInfo.CurrentStamina);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, AdventureGameplayTags::Attribute_Player_XP, InCharacterInfo.CharacterXP);
	
	InASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
}

void UDataAsset_StartUpData_Player::LevelUp(UAdventureAbilitySystemComponent* InASC, const int32 LevelUpAmount) const
{
	check(InASC && SetByCallerGameplayEffect);

	FGameplayEffectContextHandle ContextHandle = InASC->MakeEffectContext();
	ContextHandle.AddSourceObject(InASC->GetAvatarActor());

	const FGameplayEffectSpecHandle SpecHandle = InASC->MakeOutgoingSpec(SetByCallerGameplayEffect, 1.f, ContextHandle);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, AdventureGameplayTags::Attribute_Player_LevelUp, LevelUpAmount);

	InASC->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
}
