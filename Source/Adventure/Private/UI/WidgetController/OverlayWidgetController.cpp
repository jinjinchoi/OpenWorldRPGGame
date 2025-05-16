// Copyright Choi JinWoo. All Rights Reserved.


#include "UI/WidgetController/OverlayWidgetController.h"

#include "DebugHelper.h"
#include "AbilitySystem/AdventureAttributeSet.h"
#include "Character/AdventurePlayerCharacter.h"
#include "GameManager/ControllableCharacterManager.h"
#include "Player/AdventurePlayerState.h"

void UOverlayWidgetController::BroadCastInitialValue()
{
	const UAdventureAttributeSet* AdventureAttributeSet = CastChecked<UAdventureAttributeSet>(AttributeSet);

	OnHealthChangedDelegate.Broadcast(AdventureAttributeSet->GetCurrentHealth());
	OnMaxHealthChangedDelegate.Broadcast(AdventureAttributeSet->GetMaxHealth());
	OnStaminaChangeDelegate.Broadcast(AdventureAttributeSet->GetCurrentStamina());
	OnMaxStaminaChangeDelegate.Broadcast(AdventureAttributeSet->GetMaxStamina());

	if (bIsFirstSet)
	{
		Cast<AAdventurePlayerState>(PlayerState)->GetControllableCharacterManager()->BroadcastPartyCharacterInfo();
		bIsFirstSet = false;	
	}
	
}

void UOverlayWidgetController::BindCallbacksToDependencies()
{
	const UAdventureAttributeSet* AdventureAttributeSet = CastChecked<UAdventureAttributeSet>(AttributeSet);

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AdventureAttributeSet->GetCurrentHealthAttribute()).Clear();
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AdventureAttributeSet->GetMaxHealthAttribute()).Clear();
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AdventureAttributeSet->GetCurrentStaminaAttribute()).Clear();
	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AdventureAttributeSet->GetMaxStaminaAttribute()).Clear();
	OnCharacterLevelUpDelegate.Unbind();

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AdventureAttributeSet->GetCurrentHealthAttribute()).
	AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnHealthChangedDelegate.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AdventureAttributeSet->GetMaxHealthAttribute()).
	AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxHealthChangedDelegate.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AdventureAttributeSet->GetCurrentStaminaAttribute()).
	AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnStaminaChangeDelegate.Broadcast(Data.NewValue);
	});

	AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AdventureAttributeSet->GetMaxStaminaAttribute()).
	AddLambda([this](const FOnAttributeChangeData& Data)
	{
		OnMaxStaminaChangeDelegate.Broadcast(Data.NewValue);
	});

	Cast<AAdventurePlayerCharacter>(AbilitySystemComponent->GetAvatarActor())->OnMovementModeChangedDelegate.
	BindLambda([this](const ECharacterMovementType MoveType)
	{
		MovementChangeDelegate.Broadcast(MoveType);
	});

	Cast<AAdventurePlayerState>(PlayerState)->GetControllableCharacterManager()->OnPartyCharacterChangedDelegate.
	BindLambda([this](const FGameplayTag& ClassTag , int32 PartyIndex)
	{
		OnPartyCharacterChangedDelegate.Broadcast(ClassTag, PartyIndex);
	});

	OnCharacterLevelUpDelegate.BindLambda([this]()
	{
		BroadCastInitialValue();
	});
	
}

