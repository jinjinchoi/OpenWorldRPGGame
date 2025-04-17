// Copyright Choi JinWoo. All Rights Reserved.


#include "AbilitySystem/AdventureAttributeSet.h"
#include "GameplayEffectExtension.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AdventureFunctionLibrary.h"
#include "AdventureGameplayTag.h"
#include "DebugHelper.h"
#include "Controller/AdventurePlayerController.h"
#include "GameFramework/Character.h"
#include "Interface/EnemyInterface.h"
#include "Interface/PlayerInterface.h"
#include "Kismet/GameplayStatics.h"
#include "Perception/AISense_Damage.h"

void UAdventureAttributeSet::SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props)
{
	Props.EffectContextHandle = Data.EffectSpec.GetContext();
	Props.SourceASC = Data.EffectSpec.GetContext().GetOriginalInstigatorAbilitySystemComponent();

	if (IsValid(Props.SourceASC) && Props.SourceASC->AbilityActorInfo.IsValid() && Props.SourceASC->AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.SourceAvatarActor = Props.SourceASC->AbilityActorInfo->AvatarActor.Get();
		Props.SourcePlayerController = Props.SourceASC->AbilityActorInfo->PlayerController.Get();
		if (!Props.SourcePlayerController && Props.SourceAvatarActor)
		{
			if (const APawn* Pawn = Cast<APawn>(Props.SourceAvatarActor))
			{
				Props.SourcePlayerController = Pawn->GetController();
			}
		}
		if (Props.SourcePlayerController)
		{
			Props.SourceCharacter = Cast<ACharacter>(Props.SourcePlayerController->GetPawn());
		}
	}

	if (Data.Target.AbilityActorInfo.IsValid() && Data.Target.AbilityActorInfo->AvatarActor.IsValid())
	{
		Props.TargetAvatarActor = Data.Target.AbilityActorInfo->AvatarActor.Get();
		Props.TargetPlayerController = Data.Target.AbilityActorInfo->PlayerController.Get();
		Props.TargetCharacter = Cast<ACharacter>(Props.TargetAvatarActor);
		Props.TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(Props.TargetAvatarActor);
	}
}


UAdventureAttributeSet::UAdventureAttributeSet()
{
}

void UAdventureAttributeSet::PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue)
{
	Super::PreAttributeChange(Attribute, NewValue);
	
	if (Attribute == GetCurrentHealthAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.0f, GetMaxHealth());
	}
	if (Attribute == GetCurrentStaminaAttribute())
	{
		NewValue = FMath::Clamp<float>(NewValue, 0.0f, GetMaxStamina());
	}

	
}

void UAdventureAttributeSet::PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);
	
	FEffectProperties Props;
	SetEffectProperties(Data, Props);
	
	if (Data.EvaluatedData.Attribute == GetCurrentHealthAttribute())
	{
		SetCurrentHealth(FMath::Clamp(GetCurrentHealth(), 0.f, GetMaxHealth()));
	}
	if (Data.EvaluatedData.Attribute == GetCurrentStaminaAttribute())
	{
		SetCurrentStamina(FMath::Clamp(GetCurrentStamina(), 0.f, GetMaxStamina()));
	}
	if (Data.EvaluatedData.Attribute == GetIncomingDamageAttribute())
	{
		HandleIncomingDamage(Props);
	}
	if (Data.EvaluatedData.Attribute == GetIncomingStaminaCostAttribute())
	{
		HandleInComingStaminaCost(Props);
	}
	
}


void UAdventureAttributeSet::HandleIncomingDamage(const FEffectProperties& Props)
{
	const float LocalIncomingDamage = GetIncomingDamage();
	SetIncomingDamage(0.f);

	if (LocalIncomingDamage <= 0) return; // ← return If Damage is 0 or Character is invincible or Dead ↓
	if (UAdventureFunctionLibrary::DoseActorHaveTag(Props.TargetCharacter, AdventureGameplayTags::Status_Shared_Invincible)) return;
	if (GetCurrentHealth() <= 0) return;

	// execute PerfectDodge Ability When Player is Dodging
	if (UAdventureFunctionLibrary::DoseActorHaveTag(Props.TargetCharacter, AdventureGameplayTags::Status_Player_Dodging))
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			Props.TargetCharacter,
			AdventureGameplayTags::Event_PerfectDodge,
			FGameplayEventData()
		);
		return;
	}
	
	const float NewHealth = FMath::Clamp(GetCurrentHealth() - LocalIncomingDamage, 0.f, GetMaxHealth());
	SetCurrentHealth(NewHealth);
	
	if (NewHealth <= 0) // Death Logic
	{
		UAdventureFunctionLibrary::AddGameplayTagToActorIfNone(Props.TargetCharacter, AdventureGameplayTags::Status_Dead);
		
		// TODO : 소울(보상) 시스템 추가해야함.
	}
	else // Hit Logic
	{
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			Props.TargetCharacter,
			UAdventureFunctionLibrary::GetHitDirectionTag(Props.EffectContextHandle),
			FGameplayEventData()
		);

		if (Props.TargetCharacter->Implements<UEnemyInterface>()) // Enemy Logic
		{
			// Enemy's Sensing Component Update
			UAISense_Damage::ReportDamageEvent(
				Props.TargetCharacter,
				Props.TargetCharacter,
				Props.SourceCharacter,
				LocalIncomingDamage,
				Props.SourceCharacter->GetActorLocation(),
				Props.TargetCharacter->GetActorLocation()
			);
		}
	}
	
	if (UAdventureFunctionLibrary::IsCriticalHit(Props.EffectContextHandle))
	{
		// Delay Time On Critical Hit
		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(
			Props.SourceCharacter,
			AdventureGameplayTags::Event_HitPause,
			FGameplayEventData()
		);
	}
	
	// Call Show Damage Text
	ShowDamageText(Props, LocalIncomingDamage);
	
}

void UAdventureAttributeSet::ShowDamageText(const FEffectProperties& Props, const float Damage)
{
	if (Props.SourceCharacter != Props.TargetCharacter)
	{
		if (AAdventurePlayerController* PC = Cast<AAdventurePlayerController>(UGameplayStatics::GetPlayerController(Props.SourceCharacter, 0)))
		{
			const bool bIsCriticalHit = UAdventureFunctionLibrary::IsCriticalHit(Props.EffectContextHandle);
			const FGameplayTag& DamageType = UAdventureFunctionLibrary::GetDamageType(Props.EffectContextHandle);
			PC->ShowDamageNumber(Damage, Props.TargetCharacter, bIsCriticalHit, DamageType);
		}
	}
}

void UAdventureAttributeSet::HandleInComingStaminaCost(const FEffectProperties& Props)
{
	const float LocalIncomingCost = GetIncomingStaminaCost();
	SetIncomingStaminaCost(0.f);

	if (LocalIncomingCost <= 0) return;

	const float NewStamina = FMath::Clamp(GetCurrentStamina() - LocalIncomingCost, 0.f, GetMaxStamina());
	SetCurrentStamina(NewStamina);

	if (NewStamina <= 0)
	{
		if (IPlayerInterface* PlayerInterface = Cast<IPlayerInterface>(Props.SourceCharacter))
		{
			PlayerInterface->OnStaminaDepleted();
		}
	}
	
	
}
