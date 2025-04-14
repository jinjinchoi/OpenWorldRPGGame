// Copyright Choi JinWoo. All Rights Reserved.


#include "Item/Weapon/AdventureWeaponBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AdventureFunctionLibrary.h"
#include "AdventureGameplayTag.h"
#include "DebugHelper.h"
#include "Abilities/GameplayAbilityTypes.h"
#include "Components/BoxComponent.h"
#include "Interface/CombatInterface.h"

AAdventureWeaponBase::AAdventureWeaponBase()
{
	PrimaryActorTick.bCanEverTick = false;

	WeaponMesh = CreateDefaultSubobject<UStaticMeshComponent>("WeaponMesh");
	WeaponMesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	SetRootComponent(WeaponMesh);

	WeaponCollisionBox = CreateDefaultSubobject<UBoxComponent>("WeaponCollisionBox");
	WeaponCollisionBox->SetupAttachment(GetRootComponent());
	WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	WeaponCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &AAdventureWeaponBase::CollisionBoxBeginOverlap);
	WeaponCollisionBox->OnComponentEndOverlap.AddUniqueDynamic(this, &AAdventureWeaponBase::CollisionBoxEndOverlap);
	

}

void AAdventureWeaponBase::BeginPlay()
{
	Super::BeginPlay();

	if (bIsPlayerWeapon)
	{
		WeaponMesh->SetVisibility(false);
	}
	
}

void AAdventureWeaponBase::ToggleCollisionEnable(const bool bIsEnable)
{
	if (bIsEnable)
	{
		WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else
	{
		WeaponCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		OverlappedActors.Empty();
	}
}


void AAdventureWeaponBase::CollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (OverlappedActors.Contains(OtherActor)|| !OtherActor || !OtherActor->Implements<UCombatInterface>() || ICombatInterface::Execute_IsDead(OtherActor))
	{
		return;
	}

	APawn* WeaponOwningPawn = GetInstigator();
	const APawn* TargetPawn = Cast<APawn>(OtherActor);

	checkf(WeaponOwningPawn, TEXT("You need to set Instigator to %s"), *GetName());

	if (UAdventureFunctionLibrary::IsTargetPawnHostile(WeaponOwningPawn, TargetPawn))
	{
		FGameplayEventData Data;
		Data.Instigator = WeaponOwningPawn;
		Data.Target = OtherActor;

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(WeaponOwningPawn, AdventureGameplayTags::Event_Hit_Melee, Data);
		
	}
}

void AAdventureWeaponBase::CollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	const APawn* WeaponOwningPawn = GetInstigator();

	checkf(WeaponOwningPawn, TEXT("You need to set Instigator to %s"), *GetName());

	if (OtherActor != WeaponOwningPawn)
	{
		

	}
	
}
