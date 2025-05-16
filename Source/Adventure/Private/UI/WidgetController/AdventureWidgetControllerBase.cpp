// Copyright Choi JinWoo. All Rights Reserved.


#include "UI/WidgetController/AdventureWidgetControllerBase.h"

#include "Character/AdventurePlayerCharacter.h"
#include "Controller/AdventurePlayerController.h"
#include "Player/AdventureInventory.h"
#include "Player/AdventurePlayerState.h"

void UAdventureWidgetControllerBase::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
	CurrentCharacterTag = WCParams.CharacterTag;
}

void UAdventureWidgetControllerBase::SetPlayerState(APlayerState* InPlayerState)
{
	PlayerState = InPlayerState;
}

void UAdventureWidgetControllerBase::SetPlayerController(APlayerController* InPlayerController)
{
	PlayerController = InPlayerController;
}

void UAdventureWidgetControllerBase::SetCurrentCharacterTag(const FGameplayTag& InCharacterTag)
{
	CurrentCharacterTag = InCharacterTag;
}

FGameplayTag UAdventureWidgetControllerBase::GetCurrentCharacterTag()
{
	check(PlayerController);

	if (!CurrentCharacterTag.IsValid())
	{
		const AAdventurePlayerCharacter* AdventurePlayerCharacter = Cast<AAdventurePlayerCharacter>(PlayerController->GetPawn());
		check(AdventurePlayerCharacter);
		CurrentCharacterTag = AdventurePlayerCharacter->GetCharacterClassTag();
	}
	
	return CurrentCharacterTag;
}

void UAdventureWidgetControllerBase::BroadCastInitialValue()
{
	
}

void UAdventureWidgetControllerBase::BindCallbacksToDependencies()
{
}

FAbilityInfoForWidget UAdventureWidgetControllerBase::FindAbilityInfoByCurrentCharacterTag() const
{
	if (!CharacterAbilityInformation) return FAbilityInfoForWidget();

	return CharacterAbilityInformation->FindAbilityInfoByCharacterTag(CurrentCharacterTag);
}

FAbilityInfoForWidget UAdventureWidgetControllerBase::FindAbilityInfoByTag(const FGameplayTag& InCharacterTag) const
{
	if (!CharacterAbilityInformation) return FAbilityInfoForWidget();

	return CharacterAbilityInformation->FindAbilityInfoByCharacterTag(InCharacterTag);
}

int32 UAdventureWidgetControllerBase::GetMoney() const
{
	check(PlayerState);

	AAdventurePlayerState* AdventurePlayerState = CastChecked<AAdventurePlayerState>(PlayerState);
	return AdventurePlayerState->GetPickupItemInventory()->GetMoney();
	
}

void UAdventureWidgetControllerBase::AddMoney(const int32 MoneyToAdd) const
{
	check(PlayerState);

	AAdventurePlayerState* AdventurePlayerState = CastChecked<AAdventurePlayerState>(PlayerState);
	AdventurePlayerState->GetPickupItemInventory()->AddMoney(MoneyToAdd);
}