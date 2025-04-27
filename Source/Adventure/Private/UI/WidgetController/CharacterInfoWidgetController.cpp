// Copyright Choi JinWoo. All Rights Reserved.


#include "UI/WidgetController/CharacterInfoWidgetController.h"

#include "GameManager/ControllableCharacterManager.h"
#include "Player/AdventurePlayerState.h"

void UCharacterInfoWidgetController::BroadCastInitialValue()
{
	TArray<FPartyCharacterInfo> PartyCharacterInfos = GetAdventurePlayerState()->GetControllableCharacterManager()->GetOwningCharactersInfo();

	if (PartyCharacterInfos.IsEmpty()) return;

	PartyCharacterInfos.Sort([](const FPartyCharacterInfo& DataA, const FPartyCharacterInfo& DataB)
	{
		if (DataA.bIsPartyMember && DataB.bIsPartyMember)
		{
			return DataA.PartyIndex < DataB.PartyIndex;
		}

		return DataA.CharacterLevel > DataB.CharacterLevel;
	});

	for (const FPartyCharacterInfo& CharacterInfo : PartyCharacterInfos)
	{
		GetOwningCharacterInfoDelegate.Broadcast(CharacterInfo);
	}

	
}

TArray<FPartyCharacterInfo> UCharacterInfoWidgetController::GetOwningCharactersInfo()
{
	TArray<FPartyCharacterInfo> PartyCharacterInfos = GetAdventurePlayerState()->GetControllableCharacterManager()->GetOwningCharactersInfo();

	if (PartyCharacterInfos.IsEmpty()) return PartyCharacterInfos;

	PartyCharacterInfos.Sort([](const FPartyCharacterInfo& DataA, const FPartyCharacterInfo& DataB)
	{
		if (DataA.bIsPartyMember && DataB.bIsPartyMember)
		{
			return DataA.PartyIndex < DataB.PartyIndex;
		}

		return DataA.CharacterLevel > DataB.CharacterLevel;
	});

	return PartyCharacterInfos;
}


FPartyCharacterInfo UCharacterInfoWidgetController::GetOwningCharacterInfoByClassTag(const FGameplayTag& ClassTag)
{
	return *GetAdventurePlayerState()->GetControllableCharacterManager()->FindCharacterInfoInOwningCharacters(ClassTag);
}

AAdventurePlayerState* UCharacterInfoWidgetController::GetAdventurePlayerState()
{
	check(PlayerState);
	
	if (!AdventurePlayerState)
	{
		AdventurePlayerState = CastChecked<AAdventurePlayerState>(PlayerState);
	}

	return AdventurePlayerState;
}
