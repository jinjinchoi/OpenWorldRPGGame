// Copyright Choi JinWoo. All Rights Reserved.


#include "AbilitySystem/ExecCalc/ExecCalc_Damage.h"

#include "AdventureFunctionLibrary.h"
#include "AdventureGameplayTag.h"
#include "DebugHelper.h"
#include "AbilitySystem/AdventureAttributeSet.h"

struct FAdventureAttributeStatics
{
	DECLARE_ATTRIBUTE_CAPTUREDEF(AttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(DefensePower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalChance);
	DECLARE_ATTRIBUTE_CAPTUREDEF(CriticalMagnitude);
	DECLARE_ATTRIBUTE_CAPTUREDEF(SwordAttackPower);
	DECLARE_ATTRIBUTE_CAPTUREDEF(ShieldDefensePower);


	FAdventureAttributeStatics()
	{
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAdventureAttributeSet, AttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAdventureAttributeSet, DefensePower, Target, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAdventureAttributeSet, CriticalChance, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAdventureAttributeSet, CriticalMagnitude, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAdventureAttributeSet, SwordAttackPower, Source, false);
		DEFINE_ATTRIBUTE_CAPTUREDEF(UAdventureAttributeSet, ShieldDefensePower, Target, false);
	}
	
};

static const FAdventureAttributeStatics& GetAdventureStatics ()
{
	static FAdventureAttributeStatics AdventureAttributes;
	return AdventureAttributes;
}


UExecCalc_Damage::UExecCalc_Damage()
{
	RelevantAttributesToCapture.Add(GetAdventureStatics().AttackPowerDef);
	RelevantAttributesToCapture.Add(GetAdventureStatics().DefensePowerDef);
	RelevantAttributesToCapture.Add(GetAdventureStatics().CriticalChanceDef);
	RelevantAttributesToCapture.Add(GetAdventureStatics().CriticalMagnitudeDef);
	RelevantAttributesToCapture.Add(GetAdventureStatics().SwordAttackPowerDef);
	RelevantAttributesToCapture.Add(GetAdventureStatics().ShieldDefensePowerDef);
}

void UExecCalc_Damage::Execute_Implementation(const FGameplayEffectCustomExecutionParameters& ExecutionParams,
	FGameplayEffectCustomExecutionOutput& OutExecutionOutput) const
{
	const FGameplayEffectSpec& EffectSpec = ExecutionParams.GetOwningSpec();

	FAggregatorEvaluateParameters EvaluateParameters;
	EvaluateParameters.SourceTags = EffectSpec.CapturedSourceTags.GetAggregatedTags();
	EvaluateParameters.TargetTags = EffectSpec.CapturedTargetTags.GetAggregatedTags();

	FGameplayEffectContextHandle ContextHandle = EffectSpec.GetEffectContext();

	/* Source 공격력 */
	float SourceAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetAdventureStatics().AttackPowerDef, EvaluateParameters, SourceAttackPower);

	/* 무기 공격력 */
	float SwordAttackPower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetAdventureStatics().SwordAttackPowerDef, EvaluateParameters, SwordAttackPower);

	const FGameplayTag DamageType = UAdventureFunctionLibrary::GetDamageType(ContextHandle);
	float DamageMagnitude = EffectSpec.GetSetByCallerMagnitude(DamageType);
	if (DamageMagnitude > 0.f)
	{
		DamageMagnitude /= 100.f;
	}
	float BaseDamage = (SourceAttackPower + SwordAttackPower) * DamageMagnitude;

	/* Source Critical */
	float CriticalChance = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetAdventureStatics().CriticalChanceDef, EvaluateParameters, CriticalChance);

	float CriticalMagnitude = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetAdventureStatics().CriticalMagnitudeDef, EvaluateParameters, CriticalMagnitude);
	if (CriticalMagnitude > 0.f)
	{
		CriticalMagnitude /= 100;
	}

	const bool bCriticalHit = FMath::FRandRange(1.f, 100.f) < CriticalChance;
	BaseDamage = bCriticalHit ? BaseDamage * CriticalMagnitude : BaseDamage;
	UAdventureFunctionLibrary::SetIsCriticalHit(ContextHandle, bCriticalHit);

	/* Target 방어력 */
	float TargetDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetAdventureStatics().DefensePowerDef, EvaluateParameters, TargetDefensePower);

	float ShieldDefensePower = 0.f;
	ExecutionParams.AttemptCalculateCapturedAttributeMagnitude(GetAdventureStatics().ShieldDefensePowerDef, EvaluateParameters, ShieldDefensePower);

	TargetDefensePower += ShieldDefensePower;
	
	if (TargetDefensePower > 0.f)
	{
		TargetDefensePower /= 100;
	}

	const float FinalDamage = BaseDamage * (1 - TargetDefensePower);

	const FGameplayModifierEvaluatedData EvaluatedData(UAdventureAttributeSet::GetIncomingDamageAttribute(), EGameplayModOp::Override, FinalDamage);
	OutExecutionOutput.AddOutputModifier(EvaluatedData);
	
}
