// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "AdventureInGameHUD.generated.h"

struct FGameplayTag;
class UAbilitySystemComponent;
class UAttributeSet;
struct FWidgetControllerParams;
class UOverlayWidgetController;
class UAdventureUserWidget;
/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventureInGameHUD : public AHUD
{
	GENERATED_BODY()

public:
	void InitOverlay(APlayerController* PC, APlayerState* PS, UAbilitySystemComponent* ASC, UAttributeSet* AS, const FGameplayTag& CharacterTag);
	
	UOverlayWidgetController* GetOverlayWidgetController(const FWidgetControllerParams& Params);


private:
	UPROPERTY()
	TObjectPtr<UAdventureUserWidget> OverlayWidget;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UAdventureUserWidget> OverlayWidgetClass;

	UPROPERTY()
	TObjectPtr<UOverlayWidgetController> OverlayWidgetController;

	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UOverlayWidgetController> OverlayWidgetControllerClass;
	
};
