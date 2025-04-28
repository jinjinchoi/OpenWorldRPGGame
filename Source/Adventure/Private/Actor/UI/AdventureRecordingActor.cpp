// Copyright Choi JinWoo. All Rights Reserved.


#include "Actor/UI/AdventureRecordingActor.h"

#include "Components/SceneCaptureComponent2D.h"
#include "DataAsset/CharacterData/DataAsset_RecordingActorInfo.h"
#include "Engine/AssetManager.h"


AAdventureRecordingActor::AAdventureRecordingActor()
{
	PrimaryActorTick.bCanEverTick = false;

	SkeletalMeshComponent = CreateDefaultSubobject<USkeletalMeshComponent>("SkeletalMeshComponent");
	SetRootComponent(SkeletalMeshComponent);

	SceneCaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>("SceneCaptureComponent2D");
	SceneCaptureComponent2D->SetupAttachment(GetRootComponent());

}

void AAdventureRecordingActor::BP_SetCharacterTag(const FGameplayTag& CharacterTag)
{
	UpdateSkeletalMeshAndAnimation(CharacterTag);
}

void AAdventureRecordingActor::UpdateSkeletalMeshAndAnimation(const FGameplayTag& CharacterTag)
{
	SetActorHiddenInGame(true);
	GetWorldTimerManager().SetTimer(UnhideTimerHandle, this, &ThisClass::ShowCharacter, 0.1f, false);
	
	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		RecordingActorInfo.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([&CharacterTag, this]()
		{
			if (UDataAsset_RecordingActorInfo* LoadedData = RecordingActorInfo.Get())
			{
				const FRecordingInfo RecordingInfo = LoadedData->GetRecordingInfoByCharacterTag(CharacterTag);

				SkeletalMeshComponent->SetSkeletalMesh(RecordingInfo.SkeletalMesh);
				SkeletalMeshComponent->PlayAnimation(RecordingInfo.DefaultAnimSequence, true);
			}
		})
	);
}

void AAdventureRecordingActor::ShowCharacter()
{
	SetActorHiddenInGame(false);
}


void AAdventureRecordingActor::BeginPlay()
{
	Super::BeginPlay();

	SceneCaptureComponent2D->ShowOnlyActorComponents(this);
	
}

