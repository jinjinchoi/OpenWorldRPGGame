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

void AAdventurePlayerState::SetDefaultPartyMembers()
{
	if (bIsDefaultPartySet) return;
	
	for (const TPair<FGameplayTag, int>& InitialCharacterInfo : InitialPartyMembers)
	{
		if (GetControllableCharacterManager()->FindCharacterInfoInOwningCharacters(InitialCharacterInfo.Key))
		{
			continue;
		}

		FPartyCharacterInfo CharacterInfo = FPartyCharacterInfo();
		CharacterInfo.ClassTag = InitialCharacterInfo.Key;
		CharacterInfo.bIsNotSpawned = true;
		CharacterInfo.bIsPartyMember = true;
		CharacterInfo.PartyIndex = InitialCharacterInfo.Value;
		
		ControllableCharacterManager->AddOrUpdatePartyCharactersInfo(InitialCharacterInfo.Value, CharacterInfo);
	}

	bIsDefaultPartySet = true;
}

void AAdventurePlayerState::BeginPlay()
{
	Super::BeginPlay();
	
	GetControllableCharacterManager();
	GetPickupItemInventory();
	
}
