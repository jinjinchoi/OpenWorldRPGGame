// Copyright Choi JinWoo. All Rights Reserved.


#include "AbilitySystem/Abilities/AdventureDamageGameplayAbility.h"

#include "AbilitySystemBlueprintLibrary.h"


FDamageEffectParams UAdventureDamageGameplayAbility::MakeDamageEffectParams(AActor* TargetActor, FVector KnockBackDirectionOverride) const
{
	FDamageEffectParams Params;

	Params.WorldContextObject = GetAvatarActorFromActorInfo();
	Params.SourceAbilitySystemComponent = GetAbilitySystemComponentFromActorInfo();
	Params.TargetAbilitySystemComponent = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor);
	Params.AbilityLevel = GetAbilityLevel();
	Params.DamageGameplayEffectClass = DamageEffectClass;
	Params.DamageType = DamageType;
	Params.DamageCoefficient = DamageMultiplier.GetValueAtLevel(GetAbilityLevel());

	if (KnockBackForceMagnitude > 0.f)
	{
		if (KnockBackDirectionOverride.IsNearlyZero())
		{
			FRotator Rotation = (TargetActor->GetActorLocation() - GetAvatarActorFromActorInfo()->GetActorLocation()).Rotation();
			const FVector ToTarget = Rotation.Vector();
			Params.KnockBackDirection = ToTarget * KnockBackForceMagnitude;
		}
		else
		{
			KnockBackDirectionOverride.Normalize();
			Params.KnockBackDirection = KnockBackDirectionOverride * KnockBackForceMagnitude;
		}
		
	}

	return Params;
	
}
