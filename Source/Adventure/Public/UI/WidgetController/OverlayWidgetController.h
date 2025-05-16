// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UI/WidgetController/AdventureWidgetControllerBase.h"
#include "OverlayWidgetController.generated.h"

struct FOnAttributeChangeData;
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnAttributeChangeDelegate, float, NewValue);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnMovementChangeDelegate, const ECharacterMovementType, MovementType);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnPartyCharacterChangedDelegate, const FGameplayTag&, ClassTag, int32, PartyIndex);

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

	UPROPERTY(BlueprintAssignable, Category = "Character Info")
	FOnMovementChangeDelegate MovementChangeDelegate;

	UPROPERTY(BlueprintAssignable, Category = "Character Info")
	FOnPartyCharacterChangedDelegate OnPartyCharacterChangedDelegate;

private:
	bool bIsFirstSet = true;
	FDelegateHandle LevelUpHandle;
	
};
