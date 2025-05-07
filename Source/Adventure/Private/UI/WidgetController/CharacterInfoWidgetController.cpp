// Copyright Choi JinWoo. All Rights Reserved.


#include "UI/WidgetController/CharacterInfoWidgetController.h"

#include "Character/AdventurePlayerCharacter.h"
#include "Controller/AdventurePlayerController.h"
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

TMap<int32, FPartyCharacterInfo> UCharacterInfoWidgetController::GetPartyMemberInfo()
{
	return GetAdventurePlayerState()->GetControllableCharacterManager()->GetPartyMemberInfo();
}

bool UCharacterInfoWidgetController::AddToPartyMember(const FGameplayTag& CharacterTagToAdd, const int32 PartyIndexToAdd)
{
	// 파티에 추가하려는 캐릭터의 정보를 가져옴
	FPartyCharacterInfo PartyCharacterInfoToAdd = GetOwningCharacterInfoByClassTag(CharacterTagToAdd);

	if (!PartyCharacterInfoToAdd.IsValid())
	{
		return false;
	}
	
	PartyCharacterInfoToAdd.PartyIndex = PartyIndexToAdd;
	PartyCharacterInfoToAdd.bIsPartyMember = true;
	
	GetAdventurePlayerState()->GetControllableCharacterManager()->AddOrUpdatePartyCharactersInfo(PartyIndexToAdd, PartyCharacterInfoToAdd);

	TMap<int32, FPartyCharacterInfo> CurrentPartyMember = GetPartyMemberInfo();
	IPlayerInterface* PlayerCharacterInterface = CastChecked<IPlayerInterface>(PlayerController->GetPawn());
	if (CurrentPartyMember.Num() == 1)
	{
		PlayerCharacterInterface->ForceCharacterChange(PartyIndexToAdd);
	}
	else if (PlayerCharacterInterface->GetOwningCharacterTag().MatchesTagExact(CharacterTagToAdd))
	{
		PlayerCharacterInterface->ChangeCharacterPartyIndex(PartyIndexToAdd);
		// TODO: 블루프린트에서 위젯 수정해야함
	}

	return true;
}

bool UCharacterInfoWidgetController::RemoveFromPartyMemberByPartyIndex(const int32 PartyIndexToRemove)
{
	if (ChangePlayCharacterIfPossible())
	{
		GetAdventurePlayerState()->GetControllableCharacterManager()->RemovePartyCharactersInfoByPartyIndex(PartyIndexToRemove);
		return true;
	}
	
	return false;
	
	
}

bool UCharacterInfoWidgetController::RemoveFromPartyMemberByClassTag(const FGameplayTag& CharacterTagToRemove)
{
	if (ChangePlayCharacterIfPossible())
	{
		GetAdventurePlayerState()->GetControllableCharacterManager()->RemovePartyCharactersInfoByCharacterTag(CharacterTagToRemove);
		return true;
	}

	return false;
}

FPartyCharacterInfo UCharacterInfoWidgetController::GetOwningCharacterInfoByClassTag(const FGameplayTag& ClassTag)
{
	return *GetAdventurePlayerState()->GetControllableCharacterManager()->FindCharacterInfoInOwningCharacters(ClassTag);
}

bool UCharacterInfoWidgetController::ChangePlayCharacterIfPossible()
{
	TMap<int32, FPartyCharacterInfo> CurrentPartyMember = GetPartyMemberInfo();
	if (CurrentPartyMember.Num() <= 1)
	{
		return false;
	}
	
	IPlayerInterface* PlayerCharacterInterface = CastChecked<IPlayerInterface>(PlayerController->GetPawn());

	TArray<int32> IndexCandidates = {1, 2, 3};
	
	for (int32 Index : IndexCandidates)
	{
		if (CurrentPartyMember.Contains(Index))
		{
			switch (Index)
			{
			case 1 :
				PlayerCharacterInterface->Input_CharacterChange_One();
				break;
			case 2:
				PlayerCharacterInterface->Input_CharacterChange_Two();
				break;
			case 3:
				PlayerCharacterInterface->Input_CharacterChange_Three();
				break;
			default:
				break;
			}
			break;
		}
	}

	return true;
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
