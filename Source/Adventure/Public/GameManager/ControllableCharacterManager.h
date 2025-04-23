// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "ControllableCharacterManager.generated.h"

USTRUCT(BlueprintType)
struct FPartyCharacterInfo
{
	GENERATED_BODY()

	UPROPERTY()
	bool bIsNotSpawned = true;

	UPROPERTY()
	bool bIsPartyMember = false;

	UPROPERTY()
	FGameplayTag ClassTag;

	UPROPERTY()
	int32 CharacterLevel = 1;

	UPROPERTY()
	int32 CharacterXP = 0;

	UPROPERTY()
	int32 NormalAttackLevel = 1;

	UPROPERTY()
	int32 ESkillLevel = 1;

	UPROPERTY()
	int32 RSkillLevel = 1;

	UPROPERTY()
	float AttackPower = 0;

	UPROPERTY()
	float DefensePower = 0;

	UPROPERTY()
	float CriticalChance = 0;

	UPROPERTY()
	float CriticalMagnitude = 0;

	UPROPERTY()
	float CurrentHealth = 0;

	UPROPERTY()
	float MaxHealth = 0;
	
};

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
	void AddOrUpdatePartyCharactersInfo(int32 PartyIndex, const FPartyCharacterInfo& NewCharacterInfo);

	FPartyCharacterInfo* FindCharacterInfoInOwningCharacters(const FGameplayTag& InClassTag);
	FPartyCharacterInfo* FindCharacterInfoInPartyCharacterInfo(const int32 InCharacterIndex);
	void GetCharacterClassByTag(const FGameplayTag& InClassTag, const TFunction<void(TSubclassOf<ACharacter>)>& Callback);

protected:
	UPROPERTY(EditDefaultsOnly)
	TMap<FGameplayTag, TSoftClassPtr<ACharacter>> CharacterClassInfoMap;
	
	UPROPERTY()
	TArray<FPartyCharacterInfo> OwningCharacters;

	UPROPERTY()
	TMap<int32, FPartyCharacterInfo> PartyCharacterInfo;
	
	
};
