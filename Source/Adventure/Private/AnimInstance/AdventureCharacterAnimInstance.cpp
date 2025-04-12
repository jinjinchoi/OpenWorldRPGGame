// Copyright Choi JinWoo. All Rights Reserved.


#include "AnimInstance/AdventureCharacterAnimInstance.h"

#include "AdventureFunctionLibrary.h"
#include "AdventureGameplayTag.h"
#include "KismetAnimationLibrary.h"
#include "Character/AdventureBaseCharacter.h"
#include "GameFramework/CharacterMovementComponent.h"

void UAdventureCharacterAnimInstance::NativeInitializeAnimation()
{
	OwningCharacter = Cast<AAdventureBaseCharacter>(TryGetPawnOwner());
	if (OwningCharacter)
	{
		OwningMovementComponent = OwningCharacter->GetCharacterMovement();
	}
	
}

void UAdventureCharacterAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	if (!OwningCharacter || !OwningMovementComponent) return;

	Velocity = OwningCharacter->GetVelocity();
	GroundSpeed = Velocity.Size2D();

	bHasAcceleration = OwningMovementComponent->GetCurrentAcceleration().SizeSquared2D() > 0.f;
	bIsFalling = OwningMovementComponent->IsFalling();
	bIsSprint = UAdventureFunctionLibrary::DoseActorHaveTag(OwningCharacter, AdventureGameplayTags::Status_Locomotion_Sprint);
	bIsStraing = UAdventureFunctionLibrary::DoseActorHaveTag(OwningCharacter, AdventureGameplayTags::Status_Enemy_Strafing);

	LocomotionDirection = UKismetAnimationLibrary::CalculateDirection(Velocity, OwningCharacter->GetActorRotation());
	
}
