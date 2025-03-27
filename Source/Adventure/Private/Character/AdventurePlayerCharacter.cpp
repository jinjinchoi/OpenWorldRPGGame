// Copyright Choi JinWoo. All Rights Reserved.


#include "Character/AdventurePlayerCharacter.h"

#include "AdventureGameplayTag.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "Component/Input/AdventureInputComponent.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAdventurePlayerCharacter::AAdventurePlayerCharacter()
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 600.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 60.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;
	
}

void AAdventurePlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	check(InputConfigDataAsset);
	
	ULocalPlayer* LocalPlayer = GetController<APlayerController>()->GetLocalPlayer();
	UEnhancedInputLocalPlayerSubsystem* Subsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(LocalPlayer);
	check(Subsystem);
	Subsystem->AddMappingContext(InputConfigDataAsset->DefaultMappingContext, 0);

	if (UAdventureInputComponent* AdventureInputComponent = Cast<UAdventureInputComponent>(PlayerInputComponent))
	{
		AdventureInputComponent->BindLocomotionInputAction(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Look, ETriggerEvent::Triggered, &AAdventurePlayerCharacter::Input_Look);
		AdventureInputComponent->BindLocomotionInputAction(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Jump, ETriggerEvent::Triggered, &AAdventurePlayerCharacter::Jump);
		AdventureInputComponent->BindLocomotionInputAction(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Move, ETriggerEvent::Triggered, &AAdventurePlayerCharacter::Input_Move);
		AdventureInputComponent->BindLocomotionInputAction(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Sprint, ETriggerEvent::Started, &AAdventurePlayerCharacter::Input_Sprint);
		AdventureInputComponent->BindLocomotionInputAction(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Walk, ETriggerEvent::Started, &AAdventurePlayerCharacter::Input_Walk);
		AdventureInputComponent->BindLocomotionInputAction(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Wheel_Scroll, ETriggerEvent::Started, &AAdventurePlayerCharacter::Input_CameraScroll);
	}
	
}


void AAdventurePlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AAdventurePlayerCharacter::Input_CameraScroll(const FInputActionValue& InputActionValue)
{
	const float ScrollValue = InputActionValue.Get<float>() * -CameraZoomSpeed;
	
	float NewTargetArmLength =  CameraBoom->TargetArmLength + ScrollValue;
	NewTargetArmLength = FMath::Clamp(NewTargetArmLength, 150.f, 1000.f);
	
	CameraBoom->TargetArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, NewTargetArmLength, GetWorld()->GetDeltaSeconds(), 10.0f);
}

void AAdventurePlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AAdventurePlayerCharacter::Input_Sprint()
{
	if (bIsSprint)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		bIsSprint = false;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
		bIsSprint = true;
		bIsWalking = false;
	}

	//TODO : Sprint Status 태그 추가해야함

}

void AAdventurePlayerCharacter::Input_Walk()
{
	if (bIsWalking)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		bIsWalking = false;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
		bIsWalking = true;
		bIsSprint = false;
	}
}

void AAdventurePlayerCharacter::Jump()
{
	Super::Jump();
}

