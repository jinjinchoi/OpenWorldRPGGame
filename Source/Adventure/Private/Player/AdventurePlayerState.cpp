// Copyright Choi JinWoo. All Rights Reserved.


#include "Player/AdventurePlayerState.h"
#include "GameManager/ControllableCharacterManager.h"
#include "Player/AdventureInventory.h"


UControllableCharacterManager* AAdventurePlayerState::GetControllableCharacterManager()
{
	check(ControllableCharacterManagerClass);
	
	if (!ControllableCharacterManager)
	{
		ControllableCharacterManager = NewObject<UControllableCharacterManager>(this, ControllableCharacterManagerClass);
	}

	return ControllableCharacterManager;
}

UAdventureInventory* AAdventurePlayerState::GetPickupItemInventory()
{
	check(PickupItemInventoryClass);
	
	if (!PickupItemInventory)
	{
		PickupItemInventory = NewObject<UAdventureInventory>(this, PickupItemInventoryClass);
	}

	return PickupItemInventory;
}

void AAdventurePlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	GetControllableCharacterManager()->InitializeCharacterManager();
	GetPickupItemInventory();

	bIsPlayerStateSet = true;
	OnPlayerStateSetDelegate.Broadcast();
	
}
