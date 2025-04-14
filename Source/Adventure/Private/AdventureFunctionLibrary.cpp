// Copyright Choi JinWoo. All Rights Reserved.


#include "AdventureFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AdventureGameplayTag.h"
#include "GenericTeamAgentInterface.h"
#include "AdventureType/AdventureAbilityTypes.h"
#include "AdventureType/AdventureStructTypes.h"

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

bool UAdventureFunctionLibrary::IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAdventureGameplayEffectContext* AdventureContext = static_cast<const FAdventureGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AdventureContext->IsCriticalHit();
	}

	return false;
}

FVector UAdventureFunctionLibrary::GetKnockBackDirection(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAdventureGameplayEffectContext* AdventureContext = static_cast<const FAdventureGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		return AdventureContext->GetKnockBackDirection();
	}

	return FVector::ZeroVector;
}

FGameplayTag UAdventureFunctionLibrary::GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAdventureGameplayEffectContext* AdventureContext = static_cast<const FAdventureGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		if (AdventureContext->GetDamageType().IsValid())
		{
			return *AdventureContext->GetDamageType();
		}
	}

	return FGameplayTag();
	
}

void UAdventureFunctionLibrary::SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, const bool bInIsCriticalHit)
{
	if (FAdventureGameplayEffectContext* AdventureContext = static_cast<FAdventureGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AdventureContext->SetIsCriticalHit(bInIsCriticalHit);
	}
}

void UAdventureFunctionLibrary::SetKnockBackDirection(FGameplayEffectContextHandle& EffectContextHandle, const FVector& InKnockBackDirection)
{
	if (FAdventureGameplayEffectContext* AdventureContext = static_cast<FAdventureGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		AdventureContext->SetKnockBackDirection(InKnockBackDirection);
	}
}

void UAdventureFunctionLibrary::SetDamageType(FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDamageType)
{
	if (FAdventureGameplayEffectContext* AdventureContext = static_cast<FAdventureGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		const TSharedPtr<FGameplayTag> DamageType = MakeShared<FGameplayTag>(InDamageType);
		AdventureContext->SetDamageType(DamageType);
	}
}

FActiveGameplayEffectHandle UAdventureFunctionLibrary::ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams)
{
	const AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();
	FGameplayEffectContextHandle ContextHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(SourceAvatarActor);

	if (DamageEffectParams.KnockBackDirection != FVector::ZeroVector)
	{
		SetKnockBackDirection(ContextHandle, DamageEffectParams.KnockBackDirection);
	}
	if (DamageEffectParams.DamageType.IsValid())
	{
		SetDamageType(ContextHandle, DamageEffectParams.DamageType);
	}

	const FGameplayEffectSpecHandle SpecHandle = DamageEffectParams.SourceAbilitySystemComponent->MakeOutgoingSpec(
		DamageEffectParams.DamageGameplayEffectClass,
		DamageEffectParams.AbilityLevel,
		ContextHandle
	);

	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, DamageEffectParams.DamageType, DamageEffectParams.DamageCoefficient);

	return DamageEffectParams.TargetAbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data);
	
}

bool UAdventureFunctionLibrary::IsTargetPawnHostile(const APawn* QueryPawn, const APawn* TargetPawn)
{
	check(QueryPawn && TargetPawn);
	
	const IGenericTeamAgentInterface* QueryTeamAgent = Cast<IGenericTeamAgentInterface>(QueryPawn->GetController());
	const IGenericTeamAgentInterface* TargetTeamAgent = Cast<IGenericTeamAgentInterface>(TargetPawn->GetController());

	if (QueryTeamAgent && TargetTeamAgent)
	{
		return QueryTeamAgent->GetGenericTeamId() != TargetTeamAgent->GetGenericTeamId(); 
	}

	return false;
}
