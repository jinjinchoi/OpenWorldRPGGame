// Copyright Choi JinWoo. All Rights Reserved.


#include "AdventureFunctionLibrary.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AdventureGameplayTag.h"
#include "GenericTeamAgentInterface.h"
#include "AbilitySystem/AdventureAbilitySystemComponent.h"
#include "AbilitySystem/AdventureAttributeSet.h"
#include "AdventureType/AdventureAbilityTypes.h"
#include "AdventureType/AdventureStructTypes.h"
#include "Character/AdventurePlayerCharacter.h"
#include "GameManager/ControllableCharacterManager.h"
#include "Interface/CombatInterface.h"
#include "Kismet/KismetMathLibrary.h"
#include "Player/AdventurePlayerState.h"
#include "UI/HUD/AdventureInGameHUD.h"
#include "UI/WidgetController/AdventureWidgetControllerBase.h"

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



FPartyCharacterInfo UAdventureFunctionLibrary::MakePartyCharacterInfo(const AAdventurePlayerCharacter* PlayerCharacter)
{
	check(PlayerCharacter);
	
	AAdventurePlayerState* InPlayerState = PlayerCharacter->GetPlayerState<AAdventurePlayerState>();
	check(InPlayerState);

	FPartyCharacterInfo CharacterInfo = *InPlayerState->GetControllableCharacterManager()->FindCharacterInfoInOwningCharacters(PlayerCharacter->GetCharacterClassTag());
	
	CharacterInfo.WeaponTag = PlayerCharacter->EquippedSwordTag;
	CharacterInfo.ShieldTag = PlayerCharacter->EquippedShieldTag;
	
	if (const UAdventureAttributeSet* AdventureAttributeSet = Cast<UAdventureAttributeSet>(PlayerCharacter->GetAttributeSet()))
	{
		CharacterInfo.CharacterLevel = AdventureAttributeSet->GetCharacterLevel();
		CharacterInfo.CharacterXP = AdventureAttributeSet->GetXP();
		CharacterInfo.CurrentHealth = AdventureAttributeSet->GetCurrentHealth();
		CharacterInfo.CurrentStamina = AdventureAttributeSet->GetCurrentStamina();
	}
	
	if (UAdventureAbilitySystemComponent* AdventureASC = Cast<UAdventureAbilitySystemComponent>(PlayerCharacter->GetAbilitySystemComponent()))
	{
		FForEachAbility EachAbilityDelegate;
		EachAbilityDelegate.BindLambda([&CharacterInfo](const FGameplayAbilitySpec& AbilitySpec)
		{
			if (AbilitySpec.DynamicAbilityTags.HasTagExact(AdventureGameplayTags::InputTag_NormalAttack))
			{
				CharacterInfo.NormalAttackLevel = AbilitySpec.Level;
			}
			if (AbilitySpec.DynamicAbilityTags.HasTagExact(AdventureGameplayTags::InputTag_ESkill))
			{
				CharacterInfo.ESkillLevel = AbilitySpec.Level;
			}
			if (AbilitySpec.DynamicAbilityTags.HasTagExact(AdventureGameplayTags::InputTag_RSkill))
			{
				CharacterInfo.RSkillLevel = AbilitySpec.Level;
			}
		});
		
		AdventureASC->ForEachAbility(EachAbilityDelegate);
	}

	return CharacterInfo;
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

FGameplayTag UAdventureFunctionLibrary::GetHitDirectionTag(const FGameplayEffectContextHandle& EffectContextHandle)
{
	if (const FAdventureGameplayEffectContext* AdventureContext = static_cast<const FAdventureGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		if (AdventureContext->GetHitDirectionTag().IsValid())
		{
			return *AdventureContext->GetHitDirectionTag();
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

void UAdventureFunctionLibrary::SetHitDirectionTag(FGameplayEffectContextHandle& EffectContextHandle, const FGameplayTag& InDamageType)
{
	if (FAdventureGameplayEffectContext* AdventureContext = static_cast<FAdventureGameplayEffectContext*>(EffectContextHandle.Get()))
	{
		const TSharedPtr<FGameplayTag> HitDirectionTag = MakeShared<FGameplayTag>(InDamageType);
		AdventureContext->SetHitDirectionTag(HitDirectionTag);
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
	if (DamageEffectParams.HitDirectionTag.IsValid())
	{
		SetHitDirectionTag(ContextHandle, DamageEffectParams.HitDirectionTag);
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


FGameplayTag UAdventureFunctionLibrary::ComputeHitReactDirection(const AActor* InAttacker, const AActor* InTarget)
{
	check(InAttacker && InTarget);

	const FVector VictimForward = InTarget->GetActorForwardVector();
	const FVector VictimToAttackerNormalized = (InAttacker->GetActorLocation() - InTarget->GetActorLocation()).GetSafeNormal();

	const float DotResult = FVector::DotProduct(VictimForward, VictimToAttackerNormalized);
	float AngleDifference = UKismetMathLibrary::DegAcos(DotResult);

	const FVector CrossResult = FVector::CrossProduct(VictimForward, VictimToAttackerNormalized);

	if (CrossResult.Z < 0.f)
	{
		AngleDifference *= -1.f;
	}

	if (AngleDifference >= -45.f && AngleDifference <= 45.f)
	{
		return AdventureGameplayTags::Event_HitReact_Front;
	}
	else if (AngleDifference < -45.f && AngleDifference >= -135.f)
	{
		return AdventureGameplayTags::Event_HitReact_Left;
	}
	else if (AngleDifference < -135.f || AngleDifference > 135.f)
	{
		return AdventureGameplayTags::Event_HitReact_Back;
	}
	else if (AngleDifference > 45.f && AngleDifference <= 135.f)
	{
		return AdventureGameplayTags::Event_HitReact_Right;
	}

	return AdventureGameplayTags::Event_HitReact_Front;
}

void UAdventureFunctionLibrary::GetLiveActorWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin)
{
	FCollisionQueryParams SphereParams;
	SphereParams.AddIgnoredActors(ActorsToIgnore);

	TArray<FOverlapResult> OverlapResults;

	if (const UWorld* World = GEngine->GetWorldFromContextObject(WorldContextObject, EGetWorldErrorMode::LogAndReturnNull))
	{
		World->OverlapMultiByObjectType(
			OverlapResults,
			SphereOrigin,
			FQuat::Identity,
			FCollisionObjectQueryParams(FCollisionObjectQueryParams::InitType::AllDynamicObjects),
			FCollisionShape::MakeSphere(Radius),
			SphereParams
		);

	
		for (FOverlapResult& Overlap : OverlapResults)
		{
			if (Overlap.GetActor()->Implements<UCombatInterface>() && !ICombatInterface::Execute_IsDead(Overlap.GetActor()))
			{
				OutOverlappingActors.AddUnique(Overlap.GetActor());
			}
		}
		
	}
}

float UAdventureFunctionLibrary::EvaluateScalableFloatAtLevel(const FScalableFloat& Scalable, const float Level)
{
	return Scalable.GetValueAtLevel(Level);
}


UCharacterInfoWidgetController* UAdventureFunctionLibrary::GetCharacterInfoWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PlayerController = WorldContextObject->GetWorld()->GetFirstPlayerController())
	{
		if (AAdventureInGameHUD* AdventureInGameHUD = Cast<AAdventureInGameHUD>(PlayerController->GetHUD()))
		{
			const FGameplayTag CharacterTag = PlayerController->GetPawn<AAdventurePlayerCharacter>()->GetCharacterClassTag();
			
			return AdventureInGameHUD->GetCharacterInfoWidgetController(PlayerController->GetPlayerState<APlayerState>(), PlayerController, CharacterTag);
		}
	}

	return nullptr;
}

UInventoryWidgetController* UAdventureFunctionLibrary::GetInventoryWidgetController(const UObject* WorldContextObject)
{
	if (APlayerController* PlayerController = WorldContextObject->GetWorld()->GetFirstPlayerController())
	{
		if (AAdventureInGameHUD* AdventureInGameHUD = Cast<AAdventureInGameHUD>(PlayerController->GetHUD()))
		{
			const FGameplayTag CharacterTag = PlayerController->GetPawn<AAdventurePlayerCharacter>()->GetCharacterClassTag();
			
			return AdventureInGameHUD->GetInventoryWidgetController(PlayerController->GetPlayerState<APlayerState>(), PlayerController, CharacterTag);
		}
	}

	return nullptr;
}
