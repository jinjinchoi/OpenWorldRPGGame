// Cypie


#include "Character/AdventureEnemyCharacter.h"

#include "GameFramework/CharacterMovementComponent.h"

AAdventureEnemyCharacter::AAdventureEnemyCharacter()
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;
	
}
