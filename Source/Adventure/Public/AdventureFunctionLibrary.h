// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AdventureFunctionLibrary.generated.h"

struct FGameplayEffectContextHandle;
struct FDamageEffectParams;
/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	/** Gameplay Tag **/
	UFUNCTION(BlueprintPure, Category="AdventureFunctionLibrary|GameplayAbility")
	static bool DoseActorHaveTag(AActor* InActor, const FGameplayTag TagToCheck);	
	
	UFUNCTION(BlueprintCallable, Category="AdventureFunctionLibrary|GameplayAbility")
	static void AddGameplayTagToActorIfNone(AActor* InActor, const FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category="AdventureFunctionLibrary|GameplayAbility")
	static void RemoveGameplayTagToActorIfFound(AActor* InActor, const FGameplayTag TagToRemove);

	/** Effect Context **/
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);
	static FVector GetKnockBackDirection(const FGameplayEffectContextHandle& EffectContextHandle);
	static FGameplayTag GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle);

	static void SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, const bool bInIsCriticalHit);
	static void SetKnockBackDirection(FGameplayEffectContextHandle& EffectContextHandle, const FVector& InKnockBackDirection);
	static void SetDamageType(UPARAM(ref) FGameplayEffectContextHandle& EffectContextHandle,  const FGameplayTag& InDamageType);
	
	
	/** Gameplay Mechanics **/
	UFUNCTION(BlueprintCallable, Category="AdventureFunctionLibrary|GameplayAbility")
	static FActiveGameplayEffectHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);
};
