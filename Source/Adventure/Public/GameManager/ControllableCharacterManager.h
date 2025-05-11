// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "AdventureType/AdventureStructTypes.h"
#include "ControllableCharacterManager.generated.h"

DECLARE_DELEGATE_TwoParams(FOnPartyCharacterChanged, const FGameplayTag& /* Class Tag */, int32 /* PartyIndex */)

/**
 * 
 */
UCLASS(Blueprintable)
class ADVENTURE_API UControllableCharacterManager : public UObject
{
	GENERATED_BODY()

public:
	void InitializeCharacterManager();
	void AddOrUpdateOwningCharactersInfo(const FPartyCharacterInfo& NewCharacterInfo);
	void AddOrUpdatePartyCharactersInfo(const int32 IndexToAdd, const FPartyCharacterInfo& NewCharacterInfo);

    /* 파티 멤버에서 제외하는 함수 */
	void RemovePartyCharactersInfoByPartyIndex(const int32 PartyIndex);
	void RemovePartyCharactersInfoByCharacterTag(const FGameplayTag& InCharacterTag);

	FPartyCharacterInfo* FindCharacterInfoInOwningCharacters(const FGameplayTag& InClassTag);
	FPartyCharacterInfo* FindCharacterInfoByPartyIndex(const int32 InCharacterIndex);
	void GetCharacterClassByTag(const FGameplayTag& InClassTag, const TFunction<void(TSubclassOf<ACharacter>)>& Callback);

	FOnPartyCharacterChanged OnPartyCharacterChangedDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, TSoftClassPtr<ACharacter>> CharacterClassInfoMap;
	
	UPROPERTY(EditDefaultsOnly)
	TArray<FPartyCharacterInfo> DefaultCharacterInfos;
	
	UPROPERTY()
	TArray<FPartyCharacterInfo> OwningCharacters;

	UPROPERTY()
	TMap<int32 /* Party index */, FGameplayTag /* Character Tag */> PartyCharacterInfo;


private:
	void BroadcastPartyCharacterInfo();
	FPartyCharacterInfo GetPartyMemberIfInParty(const int32 PartyIndex);
	void RemovePartyMember(FPartyCharacterInfo& CharacterInfoToRemove);

public:
	FORCEINLINE TArray<FPartyCharacterInfo> GetOwningCharactersInfo() { return OwningCharacters; }
	FORCEINLINE TMap<int32, FGameplayTag> GetPartyMemberInfo() const { return PartyCharacterInfo; }
	
};
