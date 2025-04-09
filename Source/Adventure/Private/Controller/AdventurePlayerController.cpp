// Cypie


#include "Controller/AdventurePlayerController.h"

#include "AdventureGameplayTag.h"
#include "EnhancedInputSubsystems.h"
#include "Character/AdventurePlayerCharacter.h"
#include "Component/Input/AdventureInputComponent.h"
#include "GameFramework/Character.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "UI/Widget/DamageTextComponent.h"
#include "Interface/PlayerInterface.h"

void AAdventurePlayerController::ShowDamageNumber(const float DamageAmount, ACharacter* TargetCharacter, const bool bIsCriticalHit, const FGameplayTag& DamageType)
{
	check(DamageTextClass)

	if (IsValid(TargetCharacter))
	{
		UDamageTextComponent* DamageTextComponent = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextClass);
		DamageTextComponent->RegisterComponent();
		DamageTextComponent->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageTextComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageTextComponent->SetDamageText(DamageAmount, bIsCriticalHit, DamageType);
	}
	
}

void AAdventurePlayerController::BeginPlay()
{
	Super::BeginPlay();

	check(InputConfigDataAsset);

	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);
	}
	
}

void AAdventurePlayerController::SetupInputComponent()
{
	Super::SetupInputComponent();

	if (UAdventureInputComponent* AdventureInputComponent = Cast<UAdventureInputComponent>(InputComponent))
	{
		AdventureInputComponent->BindLocomotionInputAction
		(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Look, ETriggerEvent::Triggered, &ThisClass::Input_Look);
		AdventureInputComponent->BindLocomotionInputAction
		(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Jump, ETriggerEvent::Triggered, &ThisClass::Input_Jump);
		AdventureInputComponent->BindLocomotionInputAction
		(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Move, ETriggerEvent::Triggered, &ThisClass::Input_Run);
		AdventureInputComponent->BindLocomotionInputAction
		(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Move, ETriggerEvent::Completed, &ThisClass::Input_StopMove);
		AdventureInputComponent->BindLocomotionInputAction
		(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Sprint, ETriggerEvent::Started, &ThisClass::Input_Sprint_Started);
		AdventureInputComponent->BindLocomotionInputAction
		(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Sprint, ETriggerEvent::Completed, &ThisClass::Input_Sprint_Completed);
		AdventureInputComponent->BindLocomotionInputAction
		(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Walk, ETriggerEvent::Started, &ThisClass::Input_Walk);
		AdventureInputComponent->BindLocomotionInputAction
		(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Wheel_Scroll, ETriggerEvent::Triggered, &ThisClass::Input_CameraScroll);
		AdventureInputComponent->BindLocomotionInputAction
		(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Climb_Stop, ETriggerEvent::Started, &ThisClass::Input_ClimbActionCompleted);
		AdventureInputComponent->BindLocomotionInputAction
		(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Climb_Move, ETriggerEvent::Triggered, &ThisClass::Input_ClimbMovement);
		AdventureInputComponent->BindLocomotionInputAction
		(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Climb_Hop, ETriggerEvent::Started, &ThisClass::Input_ClimbHopActionStarted);

		AdventureInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &ThisClass::Input_AbilityInputPressed, &ThisClass::Input_AbilityInputReleased);
	}
	
}



void AAdventurePlayerController::Input_Look(const FInputActionValue& InputActionValue)
{
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_Look(InputActionValue);
	}
}

void AAdventurePlayerController::Input_CameraScroll(const FInputActionValue& InputActionValue)
{
}

void AAdventurePlayerController::Input_Jump()
{
}

void AAdventurePlayerController::Input_Run(const FInputActionValue& InputActionValue)
{
}

void AAdventurePlayerController::Input_StopMove()
{
}

void AAdventurePlayerController::Input_Walk()
{
}

void AAdventurePlayerController::Input_Sprint_Started()
{
}

void AAdventurePlayerController::Input_Sprint_Completed()
{
}

void AAdventurePlayerController::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
}

void AAdventurePlayerController::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
}

void AAdventurePlayerController::Input_ClimbMovement(const FInputActionValue& InputActionValue)
{
}


void AAdventurePlayerController::Input_ClimbActionCompleted()
{
}

void AAdventurePlayerController::Input_ClimbHopActionStarted(const FInputActionValue& InputActionValue)
{
}
