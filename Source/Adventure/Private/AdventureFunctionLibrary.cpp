// Copyright Choi JinWoo. All Rights Reserved.


#include "AdventureFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"

bool UAdventureFunctionLibrary::DoseActorHaveTag(AActor* InActor, const FGameplayTag TagToCheck)
{
	check(InActor);
	
	if (const UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor))
	{
		return ASC->HasMatchingGameplayTag(TagToCheck);
	}

	return false;
}

void UAdventureFunctionLibrary::AddGameplayTagToActorIfNone(AActor* InActor, const FGameplayTag TagToAdd)
{
	check(InActor);
	
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor))
	{
		if (!ASC->HasMatchingGameplayTag(TagToAdd))
		{
			ASC->AddLooseGameplayTag(TagToAdd);
		}
	}
}

void UAdventureFunctionLibrary::RemoveGameplayTagToActorIfFound(AActor* InActor, const FGameplayTag TagToRemove)
{
	check(InActor);
	if (UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InActor))
	{
		if (ASC->HasMatchingGameplayTag(TagToRemove))
		{
			ASC->RemoveLooseGameplayTag(TagToRemove);
		}
	}
}
