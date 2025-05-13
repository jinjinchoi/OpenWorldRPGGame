// Copyright Choi JinWoo. All Rights Reserved.


#include "Actor/SpawnSystem/AdventureEnemySpawnVolume.h"

#include "DebugHelper.h"
#include "Actor/SpawnSystem/AdventureEnemySpawnPoint.h"
#include "Components/SphereComponent.h"
#include "Interface/PlayerInterface.h"


AAdventureEnemySpawnVolume::AAdventureEnemySpawnVolume()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>(TEXT("SphereCollision"));
	SetRootComponent(SphereCollision);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionObjectType(ECC_WorldDynamic);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);

	

}


void AAdventureEnemySpawnVolume::BeginPlay()
{
	Super::BeginPlay();

	SphereCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnSphereBeginOverlap);
	
}

void AAdventureEnemySpawnVolume::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!OtherActor->Implements<UPlayerInterface>()) return;
	
	int32 NumSpawnPoints = SpawnPoints.Num();
	TSharedRef<int32> NumCompleted = MakeShared<int32>(0);

	for (AAdventureEnemySpawnPoint* Point : SpawnPoints)
	{
		Point->SpawnActor([this, NumCompleted, NumSpawnPoints]()
		{
			(*NumCompleted)++;
			
			if (*NumCompleted >= NumSpawnPoints)
			{
				this->SetLifeSpan(0.1f);
			}
		});
	}
}