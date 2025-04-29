// Copyright Choi JinWoo. All Rights Reserved.


#include "Item/Pickups/AdventureInventoryItem.h"

#include "Components/SphereComponent.h"
#include "Components/WidgetComponent.h"
#include "Interface/PlayerInterface.h"

AAdventureInventoryItem::AAdventureInventoryItem()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("SphereCollision");
	SetRootComponent(SphereCollision);

	InteractiveWidgetComponent = CreateDefaultSubobject<UWidgetComponent>("InteractiveWidget");
	InteractiveWidgetComponent->SetupAttachment(GetRootComponent());
	InteractiveWidgetComponent->SetVisibility(false);

}

void AAdventureInventoryItem::BeginPlay()
{
	Super::BeginPlay();

	// check(ItemTag.IsValid());

	SphereCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnSphereBeginOverlap);
	SphereCollision->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnSphereEndOverlap);
	
}

void AAdventureInventoryItem::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IPlayerInterface* AdventurePlayer = Cast<IPlayerInterface>(OtherActor))
	{
		InteractiveWidgetComponent->SetVisibility(true);
		AdventurePlayer->PickUpItemBeginOverlap(this);
	}
}

void AAdventureInventoryItem::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if (IPlayerInterface* AdventurePlayer = Cast<IPlayerInterface>(OtherActor))
	{
		InteractiveWidgetComponent->SetVisibility(false);
		AdventurePlayer->PickUpItemEndOverlap(this);
	}
}
