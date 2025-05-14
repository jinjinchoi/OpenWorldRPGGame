// Copyright Choi JinWoo. All Rights Reserved.


#include "Actor/SpawnSystem/AdventureEnemySpawnPoint.h"

#include "NavigationSystem.h"
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
			
			const FVector BaseLocation = WeakThis->GetActorLocation();
			const FVector QueryExtent = FVector(200.0f, 200.0f, 300.0f);

			FNavLocation ProjectedLocation;
			bool bFoundValidLocation = false;

			UNavigationSystemV1* NavSys = FNavigationSystem::GetCurrent<UNavigationSystemV1>(WeakThis->GetWorld());
			if (NavSys)
			{
				bFoundValidLocation = NavSys->ProjectPointToNavigation(
					BaseLocation,
					ProjectedLocation,
					QueryExtent
				);
			}

			FVector SpawnLocation = bFoundValidLocation ? ProjectedLocation.Location + FVector(0, 0, 50.0f) : BaseLocation;
			
			FTransform SpawnTransform;
			SpawnTransform.SetLocation(SpawnLocation);
			SpawnTransform.SetRotation(WeakThis->GetActorRotation().Quaternion());
			
			if (UClass* LoadedActor = WeakThis->EnemyClass.Get())
			{
				AAdventureEnemyCharacter* SpawnedEnemy = WeakThis->GetWorld()->SpawnActorDeferred<AAdventureEnemyCharacter>(LoadedActor, SpawnTransform, nullptr, nullptr, ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn);
				SpawnedEnemy->SetEnemyLevel(WeakThis->EnemyLevel);
				SpawnedEnemy->FinishSpawning(SpawnTransform);
			}

			if (OnSpawnComplete) OnSpawnComplete();
			
		})
	);
}
