// Copyright Choi JinWoo. All Rights Reserved.


#include "GameManager/ControllableCharacterManager.h"

#include "DebugHelper.h"
#include "Engine/AssetManager.h"
#include "GameFramework/Character.h"

void UControllableCharacterManager::InitializeCharacterManager()
{
	for (const FPartyCharacterInfo& DefaultCharacterInfo : DefaultCharacterInfos)
	{
		AddOrUpdateOwningCharactersInfo(DefaultCharacterInfo);
		if (DefaultCharacterInfo.bIsPartyMember)
		{
			AddOrUpdatePartyCharactersInfo(DefaultCharacterInfo.PartyIndex, DefaultCharacterInfo);
		}
	}
}

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

void UControllableCharacterManager::AddOrUpdatePartyCharactersInfo(const int32 IndexToAdd, const FPartyCharacterInfo& NewCharacterInfo)
{
	FPartyCharacterInfo* ExistingInfoAtIndex = FindCharacterInfoByPartyIndex(IndexToAdd);
	FPartyCharacterInfo* ExistingInfoOfNewCharacter = FindCharacterInfoInOwningCharacters(NewCharacterInfo.ClassTag);

	const bool bHasCharacterAtIndex = (ExistingInfoAtIndex != nullptr);
	const bool bNewCharacterIsPartyMember = ExistingInfoOfNewCharacter && ExistingInfoOfNewCharacter->bIsPartyMember;

	if (bHasCharacterAtIndex)
	{
		if (bNewCharacterIsPartyMember)
		{
			// 기존 인덱스 캐릭터 복사
			FPartyCharacterInfo OldCharacterInfo = *ExistingInfoAtIndex;
			int32 IndexOfNewCharacter = ExistingInfoOfNewCharacter->PartyIndex;

			// 기존 캐릭터를 새 캐릭터가 있던 인덱스로 이동
			OldCharacterInfo.PartyIndex = IndexOfNewCharacter;
			PartyCharacterInfo.Add(IndexOfNewCharacter, OldCharacterInfo.ClassTag);

			// 기존 위치에서 새 캐릭터 제거
			RemovePartyCharactersInfoByCharacterTag(NewCharacterInfo.ClassTag);

			// 새 캐릭터 복사본 생성 후 인덱스 설정해서 추가
			FPartyCharacterInfo NewCharacterCopy = NewCharacterInfo;
			NewCharacterCopy.PartyIndex = IndexToAdd;
			PartyCharacterInfo.Add(IndexToAdd, NewCharacterCopy.ClassTag);
			AddOrUpdateOwningCharactersInfo(OldCharacterInfo);

		}
		else
		{
			// 기존 캐릭터 제거
			RemovePartyCharactersInfoByCharacterTag(ExistingInfoAtIndex->ClassTag);
			
			// 새 캐릭터 복사본 생성 후 인덱스 설정해서 추가
			FPartyCharacterInfo NewCharacterCopy = NewCharacterInfo;
			NewCharacterCopy.PartyIndex = IndexToAdd;
			PartyCharacterInfo.Add(IndexToAdd, NewCharacterCopy.ClassTag);
			AddOrUpdateOwningCharactersInfo(*ExistingInfoAtIndex);

		}
	}
	else
	{
		if (bNewCharacterIsPartyMember)
		{
			RemovePartyCharactersInfoByCharacterTag(NewCharacterInfo.ClassTag);
		}
		
		PartyCharacterInfo.Add(IndexToAdd, NewCharacterInfo.ClassTag);

	}
	AddOrUpdateOwningCharactersInfo(NewCharacterInfo);
	BroadcastPartyCharacterInfo();

}

void UControllableCharacterManager::RemovePartyCharactersInfoByPartyIndex(const int32 PartyIndex)
{
	FPartyCharacterInfo ExistingPartyCharacterInfo = GetPartyMemberIfInParty(PartyIndex);
	RemovePartyMember(ExistingPartyCharacterInfo);
}

void UControllableCharacterManager::RemovePartyCharactersInfoByCharacterTag(const FGameplayTag& InCharacterTag)
{
	for (TPair<int, FGameplayTag>& PartyInfo : PartyCharacterInfo)
	{
		if (PartyInfo.Value.MatchesTagExact(InCharacterTag))
		{
			RemovePartyMember(*FindCharacterInfoInOwningCharacters(InCharacterTag));
			return;
		}
	}
}


void UControllableCharacterManager::RemovePartyMember(FPartyCharacterInfo& CharacterInfoToRemove)
{
	if (CharacterInfoToRemove.IsValid())
	{
		PartyCharacterInfo.Remove(CharacterInfoToRemove.PartyIndex);
		
		CharacterInfoToRemove.bIsPartyMember = false;
		CharacterInfoToRemove.PartyIndex = INT_MAX;
		AddOrUpdateOwningCharactersInfo(CharacterInfoToRemove);
		
		BroadcastPartyCharacterInfo();
	}
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

FPartyCharacterInfo* UControllableCharacterManager::FindCharacterInfoByPartyIndex(const int32 InCharacterIndex)
{
	FGameplayTag* FoundCharacterTag = PartyCharacterInfo.Find(InCharacterIndex);
	if (FoundCharacterTag)
	{
		return FindCharacterInfoInOwningCharacters(*FoundCharacterTag);
	}
	
	return nullptr;
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
	for (const TPair<int, FGameplayTag>& CharacterInfo : PartyCharacterInfo)
	{
		OnPartyCharacterChangedDelegate.ExecuteIfBound(CharacterInfo.Value, CharacterInfo.Key);
	}
}

FPartyCharacterInfo UControllableCharacterManager::GetPartyMemberIfInParty(const int32 PartyIndex)
{
	for (const FPartyCharacterInfo& ExistingPartyCharacterInfo : OwningCharacters)
	{
		if (ExistingPartyCharacterInfo.PartyIndex == PartyIndex)
		{
			return ExistingPartyCharacterInfo;
		}
	}

	return FPartyCharacterInfo();
}

