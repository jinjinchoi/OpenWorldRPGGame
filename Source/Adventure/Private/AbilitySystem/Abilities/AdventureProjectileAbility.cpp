// Copyright Choi JinWoo. All Rights Reserved.


#include "AbilitySystem/Abilities/AdventureProjectileAbility.h"

#include "Actor/AdventureProjectileBase.h"
#include "GameFramework/ProjectileMovementComponent.h"

void UAdventureProjectileAbility::SpawnProjectile(const FVector& SpawnLocation, const FVector& TargetLocation)
{
	FRotator ProjectileRotation = (TargetLocation - SpawnLocation).Rotation();
	const FVector ProjectileForwardVector = ProjectileRotation.Vector();

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(SpawnLocation);
	SpawnTransform.SetRotation(ProjectileRotation.Quaternion());

	AAdventureProjectileBase* SpawnedProjectile = GetWorld()->SpawnActorDeferred<AAdventureProjectileBase>(
		ProjectileClass,
		SpawnTransform,
		GetAvatarActorFromActorInfo(),
		Cast<APawn>(GetAvatarActorFromActorInfo()),
		ESpawnActorCollisionHandlingMethod::AdjustIfPossibleButAlwaysSpawn
	);

	SpawnedProjectile->DamageEffectParams = MakeDamageEffectParams();
	SpawnedProjectile->GetProjectileMovementComponent()->InitialSpeed = ProjectileSpeed;
	SpawnedProjectile->GetProjectileMovementComponent()->MaxSpeed = ProjectileSpeed;

	SpawnedProjectile->FinishSpawning(SpawnTransform);
	
}
