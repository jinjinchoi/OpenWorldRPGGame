// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "AdventureFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintPure, Category="AdventureFunctionLibrary|GameplayAbility")
	static bool DoseActorHaveTag(AActor* InActor, const FGameplayTag TagToCheck);	
	
	UFUNCTION(BlueprintCallable, Category="AdventureFunctionLibrary|GameplayAbility")
	static void AddGameplayTagToActorIfNone(AActor* InActor, const FGameplayTag TagToAdd);

	UFUNCTION(BlueprintCallable, Category="AdventureFunctionLibrary|GameplayAbility")
	static void RemoveGameplayTagToActorIfFound(AActor* InActor, const FGameplayTag TagToRemove);
	
};
