// Copyright Choi JinWoo. All Rights Reserved.


#include "Player/AdventurePlayerState.h"

#include "GameFramework/Character.h"
#include "GameManager/ControllableCharacterManager.h"


UControllableCharacterManager* AAdventurePlayerState::GetControllableCharacterManager()
{
	if (!ControllableCharacterManager)
	{
		ControllableCharacterManager = NewObject<UControllableCharacterManager>(this, ControllableCharacterManagerClass);
	}

	return ControllableCharacterManager;
}

void AAdventurePlayerState::BeginPlay()
{
	Super::BeginPlay();

	if (!ControllableCharacterManager)
	{
		ControllableCharacterManager = NewObject<UControllableCharacterManager>(this);
	}

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
