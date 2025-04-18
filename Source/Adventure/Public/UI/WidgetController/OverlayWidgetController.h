// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AdventureWidgetControllerBase.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeDelegate, float, NewValue);

/**
 * 
 */
UCLASS()
class ADVENTURE_API UOverlayWidgetController : public UAdventureWidgetControllerBase
{
	GENERATED_BODY()

public:
	virtual void BroadCastInitialValue() override;
	virtual void BindCallbacksToDependencies() override;
	
	UPROPERTY(BlueprintAssignable, Category = "GameplayAbility|Attribute")
	FOnAttributeChangeDelegate OnHealthChangedDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GameplayAbility|Attribute")
	FOnAttributeChangeDelegate OnMaxHealthChangedDelegate;
	
	UPROPERTY(BlueprintAssignable, Category = "GameplayAbility|Attribute")
	FOnAttributeChangeDelegate OnStaminaChangeDelegate;

	UPROPERTY(BlueprintAssignable, Category = "GameplayAbility|Attribute")
	FOnAttributeChangeDelegate OnMaxStaminaChangeDelegate;
	

	
};
