// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_InputConfig.generated.h"

class UInputAction;
class UInputMappingContext;

USTRUCT(BlueprintType)
struct FAdventureInputAction
{
	GENERATED_BODY()
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputAction> InputAction = nullptr;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag = FGameplayTag();

	bool IsValid() const
	{
		return InputAction && InputTag.IsValid();
	}
	
};

/**
 * 
 */
UCLASS()
class ADVENTURE_API UDataAsset_InputConfig : public UDataAsset
{
	GENERATED_BODY()

public:
	const UInputAction* FindLocomotionInputActionByTag(const FGameplayTag& InputTag) const;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> DefaultMappingContext;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UInputMappingContext> ClimbMappingContext;

	/* 기본적인 움직임을 담당하는 Action과 Tag를 저장하는 배열 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="InputTag"))
	TArray<FAdventureInputAction> LocomotionInputActions;
	
	/* Pressed 시 발동하는 Ability */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="InputTag"))
	TArray<FAdventureInputAction> StartedAbilityInputActions;

	/* Hold 시 발동하는 Ability */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(TitleProperty="InputTag"))
	TArray<FAdventureInputAction> TriggeredAbilityActions;
	
};
