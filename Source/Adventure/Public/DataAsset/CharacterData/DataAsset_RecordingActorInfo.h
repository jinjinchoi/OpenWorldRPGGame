// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_RecordingActorInfo.generated.h"


USTRUCT(BlueprintType)
struct FRecordingInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "CharacterClass.Player"))
	FGameplayTag CharacterTag;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<USkeletalMesh> SkeletalMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TObjectPtr<UAnimSequence> DefaultAnimSequence;
	
};

/**
 * 
 */
UCLASS()
class ADVENTURE_API UDataAsset_RecordingActorInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category= "RecordingInfo")
	TArray<FRecordingInfo> RecordingInfos;
	
	FRecordingInfo GetRecordingInfoByCharacterTag(const FGameplayTag& CharacterTag);
	
};
