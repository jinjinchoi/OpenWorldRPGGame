// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "AdventureWidgetControllerBase.generated.h"

class UAdventureAttributeSet;
class UAdventureAbilitySystemComponent;
class AAdventurePlayerState;
class AAdventurePlayerController;
/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureWidgetControllerBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	AAdventurePlayerController* GetAdventurePlayerController();

	UFUNCTION(BlueprintCallable)
	AAdventurePlayerState* GetAdventurePlayerState();

	// UFUNCTION(BlueprintCallable)
	// UAdventureAbilitySystemComponent* GetAdventureAbilitySystemComponent();
	//
	// UFUNCTION(BlueprintCallable)
	// UAdventureAttributeSet* GetAdventureAttributeSet();
	
private:
	UPROPERTY()
	TObjectPtr<AAdventurePlayerController> AdventurePlayerController;

	UPROPERTY()
	TObjectPtr<AAdventurePlayerState> AdventurePlayerState;

	UPROPERTY()
	TObjectPtr<UAdventureAbilitySystemComponent> AdventureAbilitySystemComponent;

	UPROPERTY()
	TObjectPtr<UAdventureAttributeSet> AdventureAttributeSet;
	
};
