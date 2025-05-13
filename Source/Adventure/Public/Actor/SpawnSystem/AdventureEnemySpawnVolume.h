// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AdventureEnemySpawnVolume.generated.h"

class AAdventureEnemySpawnPoint;
class USphereComponent;

UCLASS()
class ADVENTURE_API AAdventureEnemySpawnVolume : public AActor
{
	GENERATED_BODY()
	
public:	
	AAdventureEnemySpawnVolume();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<USphereComponent> SphereCollision;

	UPROPERTY(EditAnywhere, Category="Spawn Info")
	TArray<AAdventureEnemySpawnPoint*> SpawnPoints;

	UFUNCTION()
	void OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);

};
