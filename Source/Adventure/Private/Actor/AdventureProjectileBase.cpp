// Copyright Choi JinWoo. All Rights Reserved.


#include "Actor/AdventureProjectileBase.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "NiagaraFunctionLibrary.h"
#include "AbilitySystemComponent.h"
#include "AdventureFunctionLibrary.h"
#include "Components/AudioComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Interface/CombatInterface.h"
#include "Kismet/GameplayStatics.h"


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

	SphereCollision->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnSphereBeginOverlap);
	SphereCollision->OnComponentEndOverlap.AddUniqueDynamic(this, &ThisClass::OnSphereEndOverlap);

	LoopingSoundComponent = UGameplayStatics::SpawnSoundAttached(LoopingSound, GetRootComponent());
	if (LoopingSoundComponent)
	{
		LoopingSoundComponent->bStopWhenOwnerDestroyed = true;
	}
	
}

void AAdventureProjectileBase::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
}

void AAdventureProjectileBase::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
}


void AAdventureProjectileBase::OnHit() const
{
	UGameplayStatics::PlaySoundAtLocation(this, ImpactSound, GetActorLocation(), GetActorRotation());
	UNiagaraFunctionLibrary::SpawnSystemAtLocation(this, ImpactEffect, GetActorLocation());
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
	
	return UAdventureFunctionLibrary::IsTargetPawnHostile(GetInstigator(), Cast<APawn>(OtherActor));
	
}

void AAdventureProjectileBase::ApplyGameplayEffectToTargetActor(AActor* InTargetActor)
{
	if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(InTargetActor))
	{
		DamageEffectParams.TargetAbilitySystemComponent = TargetASC;
		DamageEffectParams.HitDirectionTag = UAdventureFunctionLibrary::ComputeHitReactDirection(this, InTargetActor);
		if (DamageEffectParams.KnockBackForce > 0)
		{
			const FRotator TargetRotation = (InTargetActor->GetActorLocation() - this->GetActorLocation()).Rotation();
			const FVector ToTarget = TargetRotation.Vector();
			DamageEffectParams.KnockBackDirection = ToTarget * DamageEffectParams.KnockBackForce;
		}
		UAdventureFunctionLibrary::ApplyDamageEffect(DamageEffectParams);
	}
}
