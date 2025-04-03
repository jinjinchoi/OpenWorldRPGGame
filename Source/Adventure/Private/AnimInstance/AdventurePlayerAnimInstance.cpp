// Copyright Choi JinWoo. All Rights Reserved.


#include "AnimInstance/AdventurePlayerAnimInstance.h"
#include "Character/AdventurePlayerCharacter.h"
#include "Component/Movement/AdventureMovementComponent.h"

void UAdventurePlayerAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();

	if (const AAdventurePlayerCharacter* PlayerCharacter = Cast<AAdventurePlayerCharacter>(OwningCharacter))
	{
		AdventureMovementComponent = PlayerCharacter->GetAdventureMovementComponent();
	}
	
}

void UAdventurePlayerAnimInstance::NativeThreadSafeUpdateAnimation(float DeltaSeconds)
{
	Super::NativeThreadSafeUpdateAnimation(DeltaSeconds);

	AirSpeed = OwningCharacter->GetVelocity().Z;
	bIsClimbing = AdventureMovementComponent->IsClimbing();
	
	
}
