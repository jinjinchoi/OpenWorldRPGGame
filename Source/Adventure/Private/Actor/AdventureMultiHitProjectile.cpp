// Copyright Choi JinWoo. All Rights Reserved.


#include "Actor/AdventureMultiHitProjectile.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AdventureFunctionLibrary.h"
#include "Kismet/GameplayStatics.h"


void AAdventureMultiHitProjectile::BeginPlay()
{
	Super::BeginPlay();

	GetWorld()->GetTimerManager().SetTimer(OverlappingTimer, this, &ThisClass::ApplyDamageEffectToOverlappedActors, DamageInterval, true, 0.f);
	
}

void AAdventureMultiHitProjectile::OnSphereBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                        UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if (IsValidOverlap(OtherActor))
	{
		OverlappingActors.AddUnique(OtherActor);
		return;
	}
	
	ECollisionChannel CollisionChannel = OtherActor->GetRootComponent()->GetCollisionObjectType();
	if (CollisionChannel == ECC_WorldStatic)
	{
		OnHit();
		Destroy();
	}
}

void AAdventureMultiHitProjectile::OnSphereEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor,
                                                      UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	OverlappingActors.Remove(OtherActor);
}

void AAdventureMultiHitProjectile::ApplyDamageEffectToOverlappedActors()
{
	if (OverlappingActors.IsEmpty()) return;

	for (AActor* TargetActor : OverlappingActors)
	{
		if (UAbilitySystemComponent* TargetASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(TargetActor))
		{
			DamageEffectParams.TargetAbilitySystemComponent = TargetASC;
			DamageEffectParams.HitDirectionTag = UAdventureFunctionLibrary::ComputeHitReactDirection(this, TargetActor);
			if (DamageEffectParams.KnockBackForce > 0)
			{
				FRotator TargetRotation = (TargetActor->GetActorLocation() - this->GetActorLocation()).Rotation();
				FVector ToTarget = TargetRotation.Vector();
				DamageEffectParams.KnockBackDirection = ToTarget * DamageEffectParams.KnockBackForce;
			}
			UAdventureFunctionLibrary::ApplyDamageEffect(DamageEffectParams);
		}
	}

	UGameplayStatics::PlaySoundAtLocation(this, HitSound, GetActorLocation(), GetActorRotation());
	
}