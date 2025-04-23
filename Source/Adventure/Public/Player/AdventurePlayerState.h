// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerState.h"
#include "AdventurePlayerState.generated.h"

class UControllableCharacterManager;
class ACharacter;
/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventurePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	UControllableCharacterManager* GetControllableCharacterManager();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Character")
	TSubclassOf<UControllableCharacterManager> ControllableCharacterManagerClass;
	
	UPROPERTY()
	TObjectPtr<UControllableCharacterManager> ControllableCharacterManager;

	UPROPERTY(EditDefaultsOnly, Category="Character")
	TMap<FGameplayTag /* ClassNameTag */, int32 /* PartyIndex */> InitialPartyMembers;
	
	
	
};
