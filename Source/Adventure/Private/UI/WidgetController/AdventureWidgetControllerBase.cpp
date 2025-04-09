// Copyright Choi JinWoo. All Rights Reserved.


#include "UI/WidgetController/AdventureWidgetControllerBase.h"

#include "Controller/AdventurePlayerController.h"
#include "Player/AdventurePlayerState.h"

AAdventurePlayerController* UAdventureWidgetControllerBase::GetAdventurePlayerController()
{
	if (!AdventurePlayerController)
	{
		APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		check(PlayerController);

		AdventurePlayerController = CastChecked<AAdventurePlayerController>(PlayerController);
	}

	return AdventurePlayerController;
}

AAdventurePlayerState* UAdventureWidgetControllerBase::GetAdventurePlayerState()
{
	
	if (!AdventurePlayerState)
	{
		const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
		AdventurePlayerState = PlayerController->GetPlayerState<AAdventurePlayerState>();
	}

	return AdventurePlayerState;
}

// UAdventureAbilitySystemComponent* UAdventureWidgetControllerBase::GetAdventureAbilitySystemComponent()
// {
// 	if (!AdventureAbilitySystemComponent)
// 	{
// 		const APlayerController* PlayerController = GetWorld()->GetFirstPlayerController();
// 		if (APlayerState* PlayerState = PlayerController->GetPlayerState<APlayerState>())
// 		{
// 			PlayerState->GetAbility
// 		}
// 		
// 	}
// }
//
// UAdventureAttributeSet* UAdventureWidgetControllerBase::GetAdventureAttributeSet()
// {
// }
