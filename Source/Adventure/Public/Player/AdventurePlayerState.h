// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "GameFramework/PlayerState.h"
#include "AdventurePlayerState.generated.h"

DECLARE_MULTICAST_DELEGATE(FOnPlayerStateSet);

class UAdventureInventory;
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
	UAdventureInventory* GetPickupItemInventory();
	void SetDefaultPartyMembers();

	bool bIsPlayerStateSet = false;
	FOnPlayerStateSet OnPlayerStateSetDelegate;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Character")
	TSubclassOf<UControllableCharacterManager> ControllableCharacterManagerClass;
	
	UPROPERTY()
	TObjectPtr<UControllableCharacterManager> ControllableCharacterManager;

	UPROPERTY(EditDefaultsOnly, Category="Character")
	TMap<FGameplayTag /* ClassNameTag */, int32 /* PartyIndex */> InitialPartyMembers;

	UPROPERTY(EditDefaultsOnly, Category="Inventory")
	TSubclassOf<UAdventureInventory> PickupItemInventoryClass;

	UPROPERTY()
	TObjectPtr<UAdventureInventory> PickupItemInventory;

private:
	bool bIsDefaultPartySet = false;
	
	
	
};
