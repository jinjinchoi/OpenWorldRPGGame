// Copyright Choi JinWoo. All Rights Reserved.


#include "UI/WidgetController/AdventureWidgetControllerBase.h"

#include "Controller/AdventurePlayerController.h"
#include "Player/AdventurePlayerState.h"

void UAdventureWidgetControllerBase::SetWidgetControllerParams(const FWidgetControllerParams& WCParams)
{
	PlayerController = WCParams.PlayerController;
	PlayerState = WCParams.PlayerState;
	AbilitySystemComponent = WCParams.AbilitySystemComponent;
	AttributeSet = WCParams.AttributeSet;
	CurrentCharacterTag = WCParams.CharacterTag;
}

void UAdventureWidgetControllerBase::BroadCastInitialValue()
{
	
}

void UAdventureWidgetControllerBase::BindCallbacksToDependencies()
{
}

FAbilityInfoForWidget UAdventureWidgetControllerBase::FindAbilityInfoByTag() const
{
	if (!CharacterAbilityInformation) return FAbilityInfoForWidget();

	return CharacterAbilityInformation->FindAbilityInfoByCharacterTag(CurrentCharacterTag);
}
