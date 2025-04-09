// Copyright Choi JinWoo. All Rights Reserved.


#include "Player/AdventurePlayerState.h"

#include "Character/AdventurePlayerCharacter.h"

void AAdventurePlayerState::RegisterPartyMember(const int32 PartyIndex, AAdventurePlayerCharacter* PartyMember, const bool bIsCurrentlyPlaying)
{
	check(PartyMember);

	PartyCharacterMap[PartyIndex] = PartyMember;

	if (bIsCurrentlyPlaying)
	{
		CurrentControlCharacterIndex = PartyIndex;
	}

}

void AAdventurePlayerState::SetCurrentControlCharacterIndex(const int32 InPartyIndex)
{
	CurrentControlCharacterIndex = InPartyIndex;
}

AAdventurePlayerCharacter* AAdventurePlayerState::GetCurrentControlCharacter()
{
	return PartyCharacterMap[CurrentControlCharacterIndex];
}
