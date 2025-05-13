// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TargetPoint.h"
#include "AdventureEnemySpawnPoint.generated.h"

class AAdventureEnemyCharacter;
/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventureEnemySpawnPoint : public ATargetPoint
{
	GENERATED_BODY()

public:
	void SpawnActor(TFunction<void()> OnSpawnComplete);

protected:
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Class")
	TSoftClassPtr<AAdventureEnemyCharacter> EnemyClass;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Enemy Class")
	int32 EnemyLevel = 1;
	
};
