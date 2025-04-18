// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "DataAsset/CharacterData/DataAsset_AbilityInfo.h"
#include "AdventureWidgetControllerBase.generated.h"


class UDataAsset_AbilityInfo;
class UAttributeSet;
class UAbilitySystemComponent;

USTRUCT(BlueprintType)
struct FWidgetControllerParams
{
	GENERATED_BODY()

	FWidgetControllerParams() {}
	FWidgetControllerParams(APlayerController* InPlayerController, APlayerState* InPlayerState, UAbilitySystemComponent* InAbilitySystemComponent, UAttributeSet* InAttributeSet, const FGameplayTag& InCharacterTag)
		: PlayerController(InPlayerController), PlayerState(InPlayerState), AbilitySystemComponent(InAbilitySystemComponent), AttributeSet(InAttributeSet), CharacterTag(InCharacterTag)
	{}
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerController> PlayerController = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<APlayerState> PlayerState = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent = nullptr;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	TObjectPtr<UAttributeSet> AttributeSet = nullptr;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FGameplayTag CharacterTag = FGameplayTag();
	
};

/**
 * 
 */
UCLASS(BlueprintType, Blueprintable)
class ADVENTURE_API UAdventureWidgetControllerBase : public UObject
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	void SetWidgetControllerParams(const FWidgetControllerParams& WCParams);

	UFUNCTION(BlueprintCallable)
	virtual void BroadCastInitialValue();
	
	virtual void BindCallbacksToDependencies();

	UFUNCTION(BlueprintPure)
	FAbilityInfoForWidget FindAbilityInfoByTag() const;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Widget Data")
	TObjectPtr<UDataAsset_AbilityInfo> CharacterAbilityInformation;
	
	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerController> PlayerController;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<APlayerState> PlayerState;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(BlueprintReadOnly, Category="WidgetController")
	FGameplayTag CurrentCharacterTag;

	
};
