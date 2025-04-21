// Cypie


#include "Controller/AdventurePlayerController.h"
#include "AdventureGameplayTag.h"
#include "DebugHelper.h"
#include "EnhancedInputSubsystems.h"
#include "Character/AdventurePlayerCharacter.h"
#include "Component/Input/AdventureInputComponent.h"
#include "GameFramework/Character.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "GameManager/ControllableCharacterManager.h"
#include "UI/Widget/DamageTextComponent.h"
#include "Interface/PlayerInterface.h"


AAdventurePlayerController::AAdventurePlayerController()
{
	HeroTeamId = FGenericTeamId(0);
}

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


FGenericTeamId AAdventurePlayerController::GetGenericTeamId() const
{
	return HeroTeamId;
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
		AdventureInputComponent->BindLocomotionInputAction
			(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_ChangeCharacter_One, ETriggerEvent::Started, &ThisClass::Input_ChangeCharacter_One);
		AdventureInputComponent->BindLocomotionInputAction
			(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_ChangeCharacter_Two, ETriggerEvent::Started, &ThisClass::Input_ChangeCharacter_Two);
		AdventureInputComponent->BindLocomotionInputAction
			(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_ChangeCharacter_Three, ETriggerEvent::Started, &ThisClass::Input_ChangeCharacter_Three);

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
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_CameraScroll(InputActionValue);
	}
}

void AAdventurePlayerController::Input_Jump()
{
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_Jump();
	}

}

void AAdventurePlayerController::Input_Run(const FInputActionValue& InputActionValue)
{
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_Move(InputActionValue);
	}
}

void AAdventurePlayerController::Input_StopMove()
{
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_StopMove();
	}
}

void AAdventurePlayerController::Input_Walk()
{
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_Walk();
	}
}

void AAdventurePlayerController::Input_Sprint_Started()
{
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_Sprint_Started();
	}
}

void AAdventurePlayerController::Input_Sprint_Completed()
{
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_Sprint_Completed();
	}
}

void AAdventurePlayerController::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_AbilityInputPressed(InInputTag);
	}
}

void AAdventurePlayerController::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_AbilityInputReleased(InInputTag);
	}
}



void AAdventurePlayerController::Input_ClimbMovement(const FInputActionValue& InputActionValue)
{
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_ClimbMovement(InputActionValue);
	}
}


void AAdventurePlayerController::Input_ClimbActionCompleted()
{
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_ClimbActionCompleted();
	}
}

void AAdventurePlayerController::Input_ClimbHopActionStarted(const FInputActionValue& InputActionValue)
{
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_ClimbHopActionStarted(InputActionValue);
	}
}

void AAdventurePlayerController::AddClimbMappingContext() const
{
	AddInputMappingContext(InputConfigDataAsset->ClimbMappingContext, 1);
}

void AAdventurePlayerController::RemoveClimbMappingContext() const
{
	RemoveInputMappingContext(InputConfigDataAsset->ClimbMappingContext);
}

void AAdventurePlayerController::AddInputMappingContext(const UInputMappingContext* MappingContext, const int32 InPriority) const
{
	if (!MappingContext)
	{
		DebugHelper::Print(TEXT("Can NOT access MappingContext. Please check it"), FColor::Red);
		return;
	}
	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->AddMappingContext(MappingContext, InPriority);
	}
}

void AAdventurePlayerController::RemoveInputMappingContext(const UInputMappingContext* MappingContext) const
{
	if (!MappingContext)
	{
		DebugHelper::Print(TEXT("Can NOT access MappingContext. Please check it"), FColor::Red);
		return;
	}
	if (UEnhancedInputLocalPlayerSubsystem* SubSystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(GetLocalPlayer()))
	{
		SubSystem->RemoveMappingContext(MappingContext);
	}
}

void AAdventurePlayerController::Input_ChangeCharacter_One()
{
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_CharacterChange_One();
	}
}

void AAdventurePlayerController::Input_ChangeCharacter_Two()
{
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_CharacterChange_Two();
	}
}

void AAdventurePlayerController::Input_ChangeCharacter_Three()
{
	if (IPlayerInterface* PlayerCharacterInterface = Cast<IPlayerInterface>(GetPawn()))
	{
		PlayerCharacterInterface->Input_CharacterChange_Three();
	}
}
