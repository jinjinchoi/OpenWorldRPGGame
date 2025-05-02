// Copyright Choi JinWoo. All Rights Reserved.


#include "GameManager/ControllableCharacterManager.h"

#include "Engine/AssetManager.h"
#include "GameFramework/Character.h"

void UControllableCharacterManager::AddOrUpdateOwningCharactersInfo(const FPartyCharacterInfo& NewCharacterInfo)
{
	for (FPartyCharacterInfo& ExistingPartyCharacterInfo : OwningCharacters)
	{
		if (ExistingPartyCharacterInfo.ClassTag.MatchesTagExact(NewCharacterInfo.ClassTag))
		{
			ExistingPartyCharacterInfo = NewCharacterInfo;
			return;
		}
	}

	OwningCharacters.Add(NewCharacterInfo);
	
}

void UControllableCharacterManager::AddOrUpdatePartyCharactersInfo(int32 PartyIndex, const FPartyCharacterInfo& NewCharacterInfo)
{
	PartyCharacterInfo.Add(PartyIndex, NewCharacterInfo);

	AddOrUpdateOwningCharactersInfo(NewCharacterInfo);
	BroadcastPartyCharacterInfo();
}

FPartyCharacterInfo* UControllableCharacterManager::FindCharacterInfoInOwningCharacters(const FGameplayTag& InClassTag)
{
	for (FPartyCharacterInfo& ExistingPartyCharacterInfo : OwningCharacters)
	{
		if (ExistingPartyCharacterInfo.ClassTag.MatchesTagExact(InClassTag))
		{
			return &ExistingPartyCharacterInfo;
		}
	}

	return nullptr;
}

FPartyCharacterInfo* UControllableCharacterManager::FindCharacterInfoInPartyCharacterInfo(const int32 InCharacterIndex)
{
	return PartyCharacterInfo.Find(InCharacterIndex);
}

void UControllableCharacterManager::GetCharacterClassByTag(const FGameplayTag& InClassTag, const TFunction<void(TSubclassOf<ACharacter>)>& Callback)
{
	if (const TSoftClassPtr<ACharacter>* FoundSoftClass = CharacterClassInfoMap.Find(InClassTag))
	{
		if (FoundSoftClass->IsValid())
		{
			const TSubclassOf<ACharacter> LoadedClass = FoundSoftClass->Get();
			Callback(LoadedClass);
		}
		else
		{
			UAssetManager::GetStreamableManager().RequestAsyncLoad(
				FoundSoftClass->ToSoftObjectPath(),
				FStreamableDelegate::CreateLambda([FoundSoftClass, Callback]()
				{
					const TSubclassOf<ACharacter> LoadedClass = FoundSoftClass->Get();
					Callback(LoadedClass);
				})
			);
		}
	}
	else
	{
		Callback(nullptr);
	}
}


void UControllableCharacterManager::BroadcastPartyCharacterInfo()
{
	for (const TPair<int, FPartyCharacterInfo>& CharacterInfo : PartyCharacterInfo)
	{
		bIsSuccessBoardCast = OnPartyCharacterChangedDelegate.ExecuteIfBound(CharacterInfo.Value.ClassTag, CharacterInfo.Key);
	}
}

