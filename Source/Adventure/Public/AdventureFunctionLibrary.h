// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AdventureFunctionLibrary.generated.h"

class AAdventurePlayerState;
struct FScalableFloat;
class AAdventurePlayerCharacter;
class UInventoryWidgetController;
class AAdventureInGameHUD;
class UCharacterInfoWidgetController;
class UAdventureAbilitySystemComponent;
class UAttributeSet;
struct FGameplayEffectSpecHandle;
struct FPartyCharacterInfo;
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
	
	/* Gameplay Ability System Setup */
	static FPartyCharacterInfo MakePartyCharacterInfo(const AAdventurePlayerCharacter* PlayerCharacter);

	/** Effect Context **/
	static bool IsCriticalHit(const FGameplayEffectContextHandle& EffectContextHandle);
	static FVector GetKnockBackDirection(const FGameplayEffectContextHandle& EffectContextHandle);
	static FGameplayTag GetDamageType(const FGameplayEffectContextHandle& EffectContextHandle);
	static FGameplayTag GetHitDirectionTag(const FGameplayEffectContextHandle& EffectContextHandle);

	static void SetIsCriticalHit(FGameplayEffectContextHandle& EffectContextHandle, const bool bInIsCriticalHit);
	static void SetKnockBackDirection(FGameplayEffectContextHandle& EffectContextHandle, const FVector& InKnockBackDirection);
	static void SetDamageType(FGameplayEffectContextHandle& EffectContextHandle,  const FGameplayTag& InDamageType);
	static void SetHitDirectionTag(FGameplayEffectContextHandle& EffectContextHandle,  const FGameplayTag& InDamageType);
	
	/** Gameplay Mechanics **/
	UFUNCTION(BlueprintCallable, Category="AdventureFunctionLibrary|Gameplay Mechanics")
	static FActiveGameplayEffectHandle ApplyDamageEffect(const FDamageEffectParams& DamageEffectParams);

	UFUNCTION(BlueprintPure, Category="AdventureFunctionLibrary|Gameplay Mechanics")
	static bool IsTargetPawnHostile(const APawn* QueryPawn, const APawn* TargetPawn);
	
	UFUNCTION(BlueprintPure, Category="AdventureFunctionLibrary|Gameplay Mechanics")
	static FGameplayTag ComputeHitReactDirection(const AActor* InAttacker, const AActor* InTarget);
	
	UFUNCTION(BlueprintCallable, Category="AdventureFunctionLibrary|Gameplay Mechanics")
	static void GetLiveActorWithinRadius(const UObject* WorldContextObject, TArray<AActor*>& OutOverlappingActors, const TArray<AActor*>& ActorsToIgnore, float Radius, const FVector& SphereOrigin);

	UFUNCTION(BlueprintPure, Category="AdventureFunctionLibrary|Gameplay Mechanics")
	static float EvaluateScalableFloatAtLevel(const FScalableFloat& Scalable, const float Level);


	/* Widget Controller */
	UFUNCTION(BlueprintPure, Category="AdventureFunctionLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UCharacterInfoWidgetController* GetCharacterInfoWidgetController(const UObject* WorldContextObject);

	UFUNCTION(BlueprintPure, Category="AdventureFunctionLibrary|WidgetController", meta = (DefaultToSelf = "WorldContextObject"))
	static UInventoryWidgetController* GetInventoryWidgetController(const UObject* WorldContextObject);
	
};
