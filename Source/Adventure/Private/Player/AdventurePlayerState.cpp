// Copyright Choi JinWoo. All Rights Reserved.


#include "Player/AdventurePlayerState.h"
#include "GameManager/ControllableCharacterManager.h"
#include "Player/AdventureInventory.h"


UControllableCharacterManager* AAdventurePlayerState::GetControllableCharacterManager()
{
	if (!ControllableCharacterManager)
	{
		ControllableCharacterManager = NewObject<UControllableCharacterManager>(this, ControllableCharacterManagerClass);
	}

	return ControllableCharacterManager;
}

UAdventureInventory* AAdventurePlayerState::GetPickupItemInventory()
{
	if (!PickupItemInventory)
	{
		PickupItemInventory = NewObject<UAdventureInventory>(this);
	}

	return PickupItemInventory;
}

void AAdventurePlayerState::BeginPlay()
{
	Super::BeginPlay();


	ControllableCharacterManager = NewObject<UControllableCharacterManager>(this);
	PickupItemInventory = NewObject<UAdventureInventory>(this);
	
	for (const TPair<FGameplayTag, int>& InitialCharacterInfo : InitialPartyMembers)
	{
		if (ControllableCharacterManager->FindCharacterInfoInOwningCharacters(InitialCharacterInfo.Key))
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
	
	
}
