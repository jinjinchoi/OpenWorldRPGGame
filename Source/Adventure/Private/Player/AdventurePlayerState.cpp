// Copyright Choi JinWoo. All Rights Reserved.


#include "Player/AdventurePlayerState.h"

#include "GameFramework/Character.h"
#include "GameManager/ControllableCharacterManager.h"

void AAdventurePlayerState::AddCharacterToPartyMember(ACharacter* CharacterToAdd, const int32 MemberIndex) const
{

}

UControllableCharacterManager* AAdventurePlayerState::GetControllableCharacterManager()
{
	if (!ControllableCharacterManager)
	{
		ControllableCharacterManager = NewObject<UControllableCharacterManager>(this);
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
	
	
}
