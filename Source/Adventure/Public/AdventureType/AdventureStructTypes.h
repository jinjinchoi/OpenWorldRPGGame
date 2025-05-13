// Copyright Choi JinWoo. All Rights Reserved.

#pragma once


#include "GameplayTagContainer.h"
#include "ScalableFloat.h"
#include "AdventureStructTypes.generated.h"

/**
 * 
 */

class UGameplayEffect;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FDamageEffectParams
{
	GENERATED_BODY()

	FDamageEffectParams(){}

	UPROPERTY()
	TObjectPtr<UObject> WorldContextObject = nullptr;

	UPROPERTY()
	TSubclassOf<UGameplayEffect> DamageGameplayEffectClass = nullptr;

	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> SourceAbilitySystemComponent = nullptr;
	
	UPROPERTY()
	TObjectPtr<UAbilitySystemComponent> TargetAbilitySystemComponent = nullptr;

	UPROPERTY()
	FGameplayTag DamageType = FGameplayTag();

	UPROPERTY()
	int32 AbilityLevel = 1;
	
	UPROPERTY()
	float DamageCoefficient = 0;

	UPROPERTY()
	FVector KnockBackDirection = FVector::ZeroVector;

	UPROPERTY()
	float KnockBackForce = 0.0f; 

	UPROPERTY()
	FGameplayTag HitDirectionTag = FGameplayTag();
	
	
};

USTRUCT(BlueprintType)
struct FPartyCharacterInfo
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	bool bIsPartyMember = false;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(EditCondition="bIsPartyMember"))
	int32 PartyIndex = INT_MAX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories = "CharacterClass.Player"))
	FGameplayTag ClassTag;

	UPROPERTY(BlueprintReadOnly)
	int32 CharacterLevel = 1;

	UPROPERTY(BlueprintReadOnly)
	int32 CharacterXP = 0;

	UPROPERTY(BlueprintReadOnly)
	int32 NormalAttackLevel = 1;

	UPROPERTY(BlueprintReadOnly)
	int32 ESkillLevel = 1;

	UPROPERTY(BlueprintReadOnly)
	int32 RSkillLevel = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat AttackPower;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat DefensePower;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat CriticalChance;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat CriticalMagnitude;

	UPROPERTY(VisibleDefaultsOnly, BlueprintReadOnly)
	float CurrentHealth = FLT_MAX;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FScalableFloat MaxHealth;

	UPROPERTY(VisibleDefaultsOnly)
	float CurrentStamina = FLT_MAX;

	UPROPERTY(EditDefaultsOnly)
	FScalableFloat MaxStamina;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag WeaponTag = FGameplayTag();

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag ShieldTag = FGameplayTag();

	bool IsValid() const;
	
};

USTRUCT(BlueprintType)
struct FItemSlot
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag ItemTag = FGameplayTag();
	
	UPROPERTY(BlueprintReadOnly)
	int32 Quantity = 0;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag EquippedCharacterTag = FGameplayTag();

	UPROPERTY(BlueprintReadOnly)
	FGuid SlotID;
	
};