// Cypie


#include "Character/AdventureEnemyCharacter.h"

#include "DebugHelper.h"
#include "AbilitySystem/AdventureAbilitySystemComponent.h"
#include "Components/CapsuleComponent.h"
#include "DataAsset/StartUpData/DataAsset_StartUpDataBase.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h"

AAdventureEnemyCharacter::AAdventureEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
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

void AAdventureEnemyCharacter::OnEnemyDied_Implementation()
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	if (AController* AIController = GetController())
	{
		AIController->UnPossess();
	}
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->bPauseAnims = true;
}

void AAdventureEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();
	
}

void AAdventureEnemyCharacter::InitEnemyStartUpData() const
{
	if (CharacterStartUpData.IsNull())
	{
		DebugHelper::Print(FString::Printf(TEXT("You need to assign startup data to %s"), *GetName()), FColor::Yellow);
		return;
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this]
		{
			if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
			{
				LoadedData->GiveToAbilitySystemComponent(Cast<UAdventureAbilitySystemComponent>(AbilitySystemComponent));
			}
		})
	);
	
}
