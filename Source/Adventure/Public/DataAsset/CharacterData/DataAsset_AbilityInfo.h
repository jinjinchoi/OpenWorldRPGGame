// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_AbilityInfo.generated.h"

USTRUCT(BlueprintType)
struct FAbilityInfoForWidget
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories ="CharacterClass.Player"))
	FGameplayTag CharacterTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> ESkillIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories ="Cooldown.Adventure.ESkill"))
	FGameplayTag ESkillCooldownTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> RSkillIcon;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories ="Cooldown.Adventure.RSkill"))
	FGameplayTag RSkillCooldownTag = FGameplayTag();
	
};

/**
 * 
 */
UCLASS()
class ADVENTURE_API UDataAsset_AbilityInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="AbilityInformation")
	TArray<FAbilityInfoForWidget> CharacterAbilityInfo;

	FAbilityInfoForWidget FindAbilityInfoByCharacterTag(const FGameplayTag& InCharacterTag);
	
};
