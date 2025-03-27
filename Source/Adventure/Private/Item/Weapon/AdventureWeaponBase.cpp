// Copyright Choi JinWoo. All Rights Reserved.


#include "Item/Weapon/AdventureWeaponBase.h"

#include "Components/BoxComponent.h"

AAdventureWeaponBase::AAdventureWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>("WeaponCollisionBox");
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	

}

void AAdventureWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	if (bIsPlayerWeapon)
	{
		WeaponMesh->SetVisibility(false);
	}
	
}
