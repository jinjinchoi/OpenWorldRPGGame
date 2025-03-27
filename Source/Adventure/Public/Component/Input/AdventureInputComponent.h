// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedInputComponent.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "AdventureInputComponent.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureInputComponent : public UEnhancedInputComponent
{
	GENERATED_BODY()

public:
	template <class UserClass, typename CallbackFunc>
	void BindLocomotionInputAction(const UDataAsset_InputConfig* InInputConfig, UserClass* ContextObject, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, CallbackFunc Func);
	
};

template <class UserClass, typename CallbackFunc>
void UAdventureInputComponent::BindLocomotionInputAction(const UDataAsset_InputConfig* InInputConfig,
	UserClass* ContextObject, const FGameplayTag& InInputTag, ETriggerEvent TriggerEvent, CallbackFunc Func)
{
	check(InInputConfig);

	if (const UInputAction* FoundAction = InInputConfig->FindLocomotionInputActionByTag(InInputTag))
	{
		BindAction(FoundAction, TriggerEvent, ContextObject, Func);
	}
	
}
