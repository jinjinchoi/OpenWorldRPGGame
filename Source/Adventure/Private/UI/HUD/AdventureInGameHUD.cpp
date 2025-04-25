// Copyright Choi JinWoo. All Rights Reserved.


#include "UI/HUD/AdventureInGameHUD.h"

#include "UI/Widget/AdventureUserWidget.h"
#include "UI/WidgetController/OverlayWidgetController.h"

void AAdventureInGameHUD::InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS, const FGameplayTag& CharacterTag)
{
	check(OverlayWidgetClass);

	if (!OverlayWidget)
	{
		OverlayWidget = CreateWidget<UAdventureUserWidget>(GetWorld(), OverlayWidgetClass);
	}
	
	const FWidgetControllerParams WidgetParams(PC, PS, ASC, AS, CharacterTag);
	UOverlayWidgetController* WidgetController = GetOverlayWidgetController(WidgetParams);
	OverlayWidget->SetWidgetController(WidgetController);

	WidgetController->BroadCastInitialValue();
	OverlayWidget->AddToViewport();
	
}

UOverlayWidgetController* AAdventureInGameHUD::GetOverlayWidgetController(const FWidgetControllerParams& Params)
{
	
	if (!OverlayWidgetController)
	{
		OverlayWidgetController = NewObject<UOverlayWidgetController>(this, OverlayWidgetControllerClass);
	}
	OverlayWidgetController->SetWidgetControllerParams(Params);
	OverlayWidgetController->BindCallbacksToDependencies();


	return OverlayWidgetController;
}
