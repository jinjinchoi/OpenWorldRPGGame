// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AdventureRecordingActor.generated.h"

struct FGameplayTag;
class UDataAsset_RecordingActorInfo;

UCLASS()
class ADVENTURE_API AAdventureRecordingActor : public AActor
{
	GENERATED_BODY()
	
public:	
	AAdventureRecordingActor();

	void UpdateSkeletalMeshAndAnimation(const FGameplayTag& CharacterTag) const;

protected:
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<USkeletalMeshComponent> SkeletalMeshComponent;

	UPROPERTY(EditDefaultsOnly, Category="Components")
	TObjectPtr<USceneCaptureComponent2D> SceneCaptureComponent2D;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Recording Data")
	TSoftObjectPtr<UDataAsset_RecordingActorInfo> RecordingActorInfo;

	
	
};
