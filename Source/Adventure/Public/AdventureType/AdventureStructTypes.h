// Copyright Choi JinWoo. All Rights Reserved.

#pragma once


#include "GameplayTagContainer.h"
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

	UPROPERTY()
	bool bIsNotSpawned = true;

	UPROPERTY(BlueprintReadOnly)
	bool bIsPartyMember = false;

	UPROPERTY(BlueprintReadOnly)
	int32 PartyIndex = INT_MAX;

	UPROPERTY(BlueprintReadOnly)
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

	UPROPERTY(BlueprintReadOnly)
	float AttackPower = 0;

	UPROPERTY(BlueprintReadOnly)
	float DefensePower = 0;

	UPROPERTY(BlueprintReadOnly)
	float CriticalChance = 0;

	UPROPERTY(BlueprintReadOnly)
	float CriticalMagnitude = 0;

	UPROPERTY(BlueprintReadOnly)
	float CurrentHealth = 0;

	UPROPERTY(BlueprintReadOnly)
	float MaxHealth = 0;

	UPROPERTY()
	float CurrentStamina = 0;

	UPROPERTY()
	float MaxStamina = 0;

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag WeaponTag = FGameplayTag();

	UPROPERTY(BlueprintReadOnly)
	FGameplayTag ShieldTag = FGameplayTag();
	
	
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