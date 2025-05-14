// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "AdventureGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureGameInstance : public UGameInstance
{
	GENERATED_BODY()

public:
	virtual void Init() override;

protected:
	void OnPreLoadMap(const FString& MapName);
	void OnDestinationWorldLoaded(UWorld* LoadedWorld);
	
};
