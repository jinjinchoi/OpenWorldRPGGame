// Copyright Choi JinWoo. All Rights Reserved.


#include "AnimInstance/AdventurePlayerAnimInstance.h"

#include "AdventureFunctionLibrary.h"
#include "AdventureGameplayTag.h"
#include "DebugHelper.h"
#include "Character/AdventurePlayerCharacter.h"
#include "Component/Movement/AdventureMovementComponent.h"

void UAdventurePlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (OwningMovementComponent)
	{
		AdventureMovementComponent = Cast<UAdventureMovementComponent>(OwningMovementComponent);
	}
	
}

void UAdventurePlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	if (!OwningCharacter || !AdventureMovementComponent) return;
	
	AirSpeed = OwningCharacter->GetVelocity().Z;
	bIsClimbing = AdventureMovementComponent->IsClimbing();
	ClimbVelocity = AdventureMovementComponent->GetUnRotatedClimbVelocity();
	bIsLockOn = UAdventureFunctionLibrary::DoseActorHaveTag(OwningCharacter, AdventureGameplayTags::Status_Player_TargetLock);

	
	
}
