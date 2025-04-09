// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AdventureInGameHUD.generated.h"

class UAdventureUserWidget;
/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventureInGameHUD : public AHUD
{
	GENERATED_BODY()

private:
	UPROPERTY()
	TObjectPtr<UAdventureUserWidget> OverlayWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAdventureUserWidget> OverlayWidgetClass;
	
};
