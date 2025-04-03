// Copyright Choi JinWoo. All Rights Reserved.


#include "Character/AdventurePlayerCharacter.h"

#include "AdventureGameplayTag.h"
#include "DebugHelper.h"
#include "Camera/CameraComponent.h"
#include "EnhancedInputSubsystems.h"
#include "AbilitySystem/AdventureAbilitySystemComponent.h"
#include "Component/Input/AdventureInputComponent.h"
#include "Component/Movement/AdventureMovementComponent.h"
#include "DataAsset/Input/DataAsset_InputConfig.h"
#include "DataAsset/StartUpData/DataAsset_StartUpDataBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"

AAdventurePlayerCharacter::AAdventurePlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 60.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	AdventureMovementComponent = Cast<UAdventureMovementComponent>(GetCharacterMovement());

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
		AdventureInputComponent->BindLocomotionInputAction(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Move, ETriggerEvent::Completed, &AAdventurePlayerCharacter::StopMove);
		AdventureInputComponent->BindLocomotionInputAction(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Sprint, ETriggerEvent::Started, &AAdventurePlayerCharacter::Input_Sprint_Started);
		AdventureInputComponent->BindLocomotionInputAction(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Sprint, ETriggerEvent::Completed, &AAdventurePlayerCharacter::Input_Sprint_Completed);
		AdventureInputComponent->BindLocomotionInputAction(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Walk, ETriggerEvent::Started, &AAdventurePlayerCharacter::Input_Walk);
		AdventureInputComponent->BindLocomotionInputAction(InputConfigDataAsset, this, AdventureGameplayTags::InputTag_Wheel_Scroll, ETriggerEvent::Triggered, &AAdventurePlayerCharacter::Input_CameraScroll);

		AdventureInputComponent->BindAbilityInputAction(InputConfigDataAsset, this, &AAdventurePlayerCharacter::Input_AbilityInputPressed, &AAdventurePlayerCharacter::Input_AbilityInputReleased);
	}
	
}


void AAdventurePlayerCharacter::ShowWeaponMesh_Implementation()
{
	SetWeaponMeshVisibility(true);
}

void AAdventurePlayerCharacter::HideWeaponMesh_Implementation()
{
	SetWeaponMeshVisibility(false);
}

void AAdventurePlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	
	if (!CharacterStartUpData.IsNull())
	{
		UAdventureAbilitySystemComponent* AdventureAbilitySystemComponent = Cast<UAdventureAbilitySystemComponent>(AbilitySystemComponent);
		check(AdventureAbilitySystemComponent);
		
		if (UDataAsset_StartUpDataBase* LoadedDataAsset = CharacterStartUpData.LoadSynchronous())
		{
			check(AdventureAbilitySystemComponent);
			
			LoadedDataAsset->GiveToAbilitySystemComponent(AdventureAbilitySystemComponent);
		}
	}
	else
	{
		DebugHelper::Print(FString::Printf(TEXT("You need to assign startup data to %s"), *GetName()), FColor::Yellow);
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
	NewTargetArmLength = FMath::Clamp(NewTargetArmLength, 150.f, 800.f);
	
	CameraBoom->TargetArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, NewTargetArmLength, GetWorld()->GetDeltaSeconds(), 10.0f);
}

void AAdventurePlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	ClimbActionStarted();

	if (AdventureMovementComponent && AdventureMovementComponent->IsClimbing())
	{
		ClimbMovement(InputActionValue);
		return;
	}
	
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

void AAdventurePlayerCharacter::StopMove()
{
	if (bIsSprint)
	{
		StopSprint();
	}
}

void AAdventurePlayerCharacter::ClimbMovement(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();

	const FVector ForwardDirection = FVector::CrossProduct(
		-AdventureMovementComponent->GetClimbableSurfaceNormal(),
		GetActorRightVector()
	);

	const FVector RightDirection = FVector::CrossProduct(
		-AdventureMovementComponent->GetClimbableSurfaceNormal(),
		-GetActorUpVector()
	);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
	
}


void AAdventurePlayerCharacter::Input_Sprint_Started()
{

	GetWorld()->GetTimerManager().SetTimer(SprintTimerHandle, this, &AAdventurePlayerCharacter::StartSprint, 0.5f, false);
	
}

void AAdventurePlayerCharacter::Input_Sprint_Completed()
{
	if (!bIsSprint)
	{
		GetWorld()->GetTimerManager().ClearTimer(SprintTimerHandle);
	}
}

void AAdventurePlayerCharacter::StartSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	bIsSprint = true;
	bIsWalking = false;

	// TODO: Add Sprint Tag
}

void AAdventurePlayerCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	bIsSprint = false;
	GetWorld()->GetTimerManager().ClearTimer(SprintTimerHandle);

	// TODO: Remove Sprint Tag
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

void AAdventurePlayerCharacter::Input_AbilityInputPressed(FGameplayTag InInputTag)
{
	if (UAdventureAbilitySystemComponent* AdventureASC = Cast<UAdventureAbilitySystemComponent>(AbilitySystemComponent))
	{
		AdventureASC->OnAbilityInputPressed(InInputTag);
	}
}

void AAdventurePlayerCharacter::Input_AbilityInputReleased(FGameplayTag InInputTag)
{
	if (UAdventureAbilitySystemComponent* AdventureASC = Cast<UAdventureAbilitySystemComponent>(AbilitySystemComponent))
	{
		AdventureASC->OnAbilityInputReleased(InInputTag);
	}
}

void AAdventurePlayerCharacter::ClimbActionStarted()
{
	if (!AdventureMovementComponent) return;

	if (!AdventureMovementComponent->IsClimbing())
	{
		AdventureMovementComponent->ToggleClimbing(true);
	}
	
}

void AAdventurePlayerCharacter::ClimbActionCompleted()
{
	if (!AdventureMovementComponent) return;

	if (AdventureMovementComponent->IsClimbing())
	{
		AdventureMovementComponent->ToggleClimbing(false);
	}
}



