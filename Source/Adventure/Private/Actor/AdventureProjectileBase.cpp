// Copyright Choi JinWoo. All Rights Reserved.


#include "Actor/AdventureProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AdventureFunctionLibrary.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interface/CombatInterface.h"


AAdventureProjectileBase::AAdventureProjectileBase()
{
	PrimaryActorTick.bCanEverTick = false;

	SphereCollision = CreateDefaultSubobject<USphereComponent>("Sphere Collision");
	SetRootComponent(SphereCollision);
	SphereCollision->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	SphereCollision->SetCollisionResponseToAllChannels(ECR_Ignore);
	SphereCollision->SetCollisionResponseToChannel(ECC_WorldDynamic, ECR_Overlap);
	SphereCollision->SetCollisionResponseToChannel(ECC_WorldStatic, ECR_Overlap);
	SphereCollision->SetCollisionResponseToChannel(ECC_Pawn, ECR_Overlap);
	ProjectileMovement = CreateDefaultSubobject<UProjectileMovementComponent>("ProjectileMovement");

	

}


void AAdventureProjectileBase::BeginPlay()
{
	Super::BeginPlay();

	SetLifeSpan(LifeSpan);

	SphereCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnSphereOverlap);
	
	
}

void AAdventureProjectileBase::OnSphereOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (!IsValidOverlap(OtherActor)) return;

	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(OtherActor))
	{
		// FRotator Rotation = GetActorRotation();
		// const FVector KnockBackDirection = Rotation.Vector();
		// DamageEffectParams.KnockBackDirection = KnockBackDirection * DamageEffectParams.KnockBackForce;
	}
	
	
}

bool AAdventureProjectileBase::IsValidOverlap(AActor* OtherActor) const
{
	if (!DamageEffectParams.SourceAbilitySystemComponent || !OtherActor->Implements<UCombatInterface>())
	{
		return false;
	}

	AActor* SourceAvatarActor = DamageEffectParams.SourceAbilitySystemComponent->GetAvatarActor();

	if (SourceAvatarActor == OtherActor)
	{
		return false;
	}

	const APawn* TargetPawn = Cast<APawn>(OtherActor);
	
	return UAdventureFunctionLibrary::IsTargetPawnHostile(GetInstigator(), TargetPawn);
	
}
