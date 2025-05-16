// Copyright Choi JinWoo. All Rights Reserved.


#include "UI/WidgetController/CharacterInfoWidgetController.h"

#include "DebugHelper.h"
#include "Character/AdventurePlayerCharacter.h"
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
		
		if (DataA.bIsPartyMember != DataB.bIsPartyMember)
		{
			return DataA.bIsPartyMember;
		}
		
		return DataA.CharacterLevel > DataB.CharacterLevel;
	});

	return PartyCharacterInfos;
}

TMap<int32, FGameplayTag> UCharacterInfoWidgetController::GetPartyMemberInfo()
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

	TMap<int32, FGameplayTag> CurrentPartyMember = GetPartyMemberInfo();
	IPlayerInterface* PlayerCharacterInterface = CastChecked<IPlayerInterface>(PlayerController->GetPawn());
	
	if (PlayerCharacterInterface->GetOwningCharacterTag().MatchesTagExact(CharacterTagToAdd))
	{
		PlayerCharacterInterface->ChangeCharacterPartyIndex(PartyIndexToAdd);
	}
	else if (CurrentPartyMember.Num() == 1)
	{
		PlayerCharacterInterface->ForceCharacterChange(PartyIndexToAdd);
	}

	return true;
}


bool UCharacterInfoWidgetController::RemoveFromPartyMemberByClassTag(const FGameplayTag& CharacterTagToRemove)
{
	if (!CanChangeCharacter()) return false;
	
	GetAdventurePlayerState()->GetControllableCharacterManager()->RemovePartyCharactersInfoByCharacterTag(CharacterTagToRemove);

	if (CharacterTagToRemove == GetCurrentCharacterTag())
	{
		ChangeCharacterIfCurrentPlayCharacterChanged();
	}
	
	return true;
	
}

bool UCharacterInfoWidgetController::LevelUp(const FGameplayTag& CharacterTagToLevelUp)
{
	// temporary code
	if (GetMoney() < 200)
	{
		return false;
	}
	AddMoney(-200);
	///////
	
	if (GetCurrentCharacterTag().MatchesTagExact(CharacterTagToLevelUp))
	{
		// Controlled Character
		IPlayerInterface* PlayerCharacterInterface = CastChecked<IPlayerInterface>(PlayerController->GetPawn());
		PlayerCharacterInterface->LevelUp();
		OnCharacterLevelUpDelegate.ExecuteIfBound();
	}
	else 
	{
		// Not Controlled Character
		FPartyCharacterInfo CharacterInfoToLevelUp = GetOwningCharacterInfoByClassTag(CharacterTagToLevelUp);

		if (!CharacterInfoToLevelUp.IsValid())
		{
			return false;
		}

		CharacterInfoToLevelUp.CharacterLevel += 1;
		CharacterInfoToLevelUp.CurrentHealth = FLT_MAX;
		CharacterInfoToLevelUp.CurrentStamina = FLT_MAX;
		GetAdventurePlayerState()->GetControllableCharacterManager()->AddOrUpdateOwningCharactersInfo(CharacterInfoToLevelUp);
	}
	
	return true;
}

FPartyCharacterInfo UCharacterInfoWidgetController::GetOwningCharacterInfoByClassTag(const FGameplayTag& ClassTag)
{
	return *GetAdventurePlayerState()->GetControllableCharacterManager()->FindCharacterInfoInOwningCharacters(ClassTag);
}

bool UCharacterInfoWidgetController::CanChangeCharacter()
{
	TMap<int32, FGameplayTag> CurrentPartyMember = GetPartyMemberInfo();
	if (CurrentPartyMember.Num() <= 1)
	{
		return false;
	}

	return true;
}

void UCharacterInfoWidgetController::ChangeCharacterIfCurrentPlayCharacterChanged()
{
	TMap<int32, FGameplayTag> CurrentPartyMember = GetPartyMemberInfo();
		
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
