// Copyright Choi JinWoo. All Rights Reserved.


#include "Actor/SpawnSystem/AdventureEnemySpawnPoint.h"

#include "Character/AdventureEnemyCharacter.h"
#include "Engine/AssetManager.h"

void AAdventureEnemySpawnPoint::SpawnActor(TFunction<void()> OnSpawnComplete)
{
	check(!EnemyClass.IsNull());

	TWeakObjectPtr<AAdventureEnemySpawnPoint> WeakThis(this);

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		EnemyClass.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([WeakThis, OnSpawnComplete]
		{
			if (!WeakThis.IsValid()) return;
			
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(WeakThis->GetActorLocation());
			SpawnTransform.SetRotation(WeakThis->GetActorRotation().Quaternion());
			
			if (UClass* LoadedActor = WeakThis->EnemyClass.Get())
			{
				AAdventureEnemyCharacter* SpawnedEnemy = WeakThis->GetWorld()->SpawnActorDeferred<AAdventureEnemyCharacter>(LoadedActor, SpawnTransform);
				SpawnedEnemy->SetEnemyLevel(WeakThis->EnemyLevel);

				SpawnedEnemy->FinishSpawning(SpawnTransform);
				
			}

			if (OnSpawnComplete) OnSpawnComplete();
			
		})
	);
}
