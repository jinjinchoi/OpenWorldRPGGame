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
	void AddOrUpdateOwningCharactersInfo(const FPartyCharacterInfo& NewCharacterInfo);
	
	/* 파티 멤버에 추가하는 함수. OwingCharacters 배열도 업데이트 진행하므로 따로 업데이트 할 필요 없음. */
	void AddOrUpdatePartyCharactersInfo(const int32 PartyIndex, const FPartyCharacterInfo& NewCharacterInfo);

    /* 파티 멤버에서 제외하는 함수 */
	void RemovePartyCharactersInfoByPartyIndex(const int32 PartyIndex);

	FPartyCharacterInfo* FindCharacterInfoInOwningCharacters(const FGameplayTag& InClassTag);
	FPartyCharacterInfo* FindCharacterInfoInPartyCharacterInfo(const int32 InCharacterIndex);
	void GetCharacterClassByTag(const FGameplayTag& InClassTag, const TFunction<void(TSubclassOf<ACharacter>)>& Callback);

	FOnPartyCharacterChanged OnPartyCharacterChangedDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, TSoftClassPtr<ACharacter>> CharacterClassInfoMap;
	
	UPROPERTY()
	TArray<FPartyCharacterInfo> OwningCharacters;

	UPROPERTY()
	TMap<int32, FPartyCharacterInfo> PartyCharacterInfo;

private:
	void BroadcastPartyCharacterInfo();
	FPartyCharacterInfo GetPartyMemberIfInParty(const int32 PartyIndex);
	
	bool bIsSuccessBoardCast = false;

public:
	FORCEINLINE TArray<FPartyCharacterInfo> GetOwningCharactersInfo() { return OwningCharacters; }
	FORCEINLINE TMap<int32, FPartyCharacterInfo> GetPartyMemberInfo() const { return PartyCharacterInfo; }
	
};
