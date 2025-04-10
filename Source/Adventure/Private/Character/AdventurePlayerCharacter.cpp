// Copyright Choi JinWoo. All Rights Reserved.


#include "Character/AdventurePlayerCharacter.h"
#include "DebugHelper.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystem/AdventureAbilitySystemComponent.h"
#include "Component/Input/AdventureInputComponent.h"
#include "Component/Movement/AdventureMovementComponent.h"
#include "Controller/AdventurePlayerController.h"
#include "DataAsset/StartUpData/DataAsset_StartUpDataBase.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "UI/HUD/AdventureInGameHUD.h"

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


void AAdventurePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AdventureMovementComponent)
	{
		AdventureMovementComponent->OnEnterClimbStateDelegate.BindUObject(this, &AAdventurePlayerCharacter::OnPlayerEnterClimbState);
		AdventureMovementComponent->OnExitClimbStateDelegate.BindUObject(this, &AAdventurePlayerCharacter::OnPlayerExitClimbState);
	}

	if (bIsFirstLoading)
	{
		if (AAdventurePlayerController* PlayerController = Cast<AAdventurePlayerController>(GetController()))
		{
			PlayerController->AddDefaultCharacterToManager(this);
		}

		bIsFirstLoading = false;
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
	
	InitPlayerStartUpData();
	
}

void AAdventurePlayerCharacter::InitPlayerStartUpData() const
{
	if (CharacterStartUpData.IsNull())
	{
		DebugHelper::Print(FString::Printf(TEXT("You need to assign startup data to %s"), *GetName()), FColor::Yellow);
		return;
	}
	
	UAdventureAbilitySystemComponent* AdventureAbilitySystemComponent = Cast<UAdventureAbilitySystemComponent>(AbilitySystemComponent);
	check(AdventureAbilitySystemComponent);
	
	if (UDataAsset_StartUpDataBase* LoadedDataAsset = CharacterStartUpData.LoadSynchronous())
	{
		check(AdventureAbilitySystemComponent);
		
		LoadedDataAsset->GiveToAbilitySystemComponent(AdventureAbilitySystemComponent);
	}

	if (AAdventurePlayerController* PlayerController = Cast<AAdventurePlayerController>(GetController()))
	{
		 if (AAdventureInGameHUD* AdventureInGameHUD = Cast<AAdventureInGameHUD>(PlayerController->GetHUD()))
		 {
		 	AdventureInGameHUD->InitOverlay(PlayerController, GetPlayerState(), AdventureAbilitySystemComponent, AttributeSet);
		 }
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
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y >= 0)
	{
		TryClimbAction();
	}

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

void AAdventurePlayerCharacter::Input_StopMove()
{
	if (bIsSprint)
	{
		StopSprint();
	}
}

void AAdventurePlayerCharacter::Input_ClimbMovement(const FInputActionValue& InputActionValue)
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


void AAdventurePlayerCharacter::Input_Jump()
{
	Super::Jump();
}

void AAdventurePlayerCharacter::Input_AbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (AdventureMovementComponent && AdventureMovementComponent->IsClimbing()) return;
	
	if (UAdventureAbilitySystemComponent* AdventureASC = Cast<UAdventureAbilitySystemComponent>(AbilitySystemComponent))
	{
		AdventureASC->OnAbilityInputPressed(InInputTag);
	}
}

void AAdventurePlayerCharacter::Input_AbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (AdventureMovementComponent && AdventureMovementComponent->IsClimbing()) return;
	
	if (UAdventureAbilitySystemComponent* AdventureASC = Cast<UAdventureAbilitySystemComponent>(AbilitySystemComponent))
	{
		AdventureASC->OnAbilityInputReleased(InInputTag);
	}
}

void AAdventurePlayerCharacter::TryClimbAction()
{
	if (!AdventureMovementComponent) return;

	if (!AdventureMovementComponent->IsClimbing())
	{
		AdventureMovementComponent->ToggleClimbing(true);
	}
	
}

void AAdventurePlayerCharacter::Input_ClimbActionCompleted()
{
	if (!AdventureMovementComponent) return;

	if (AdventureMovementComponent->IsClimbing())
	{
		AdventureMovementComponent->ToggleClimbing(false);
	}
}

void AAdventurePlayerCharacter::Input_ClimbHopActionStarted(const FInputActionValue& InputActionValue)
{
	if (AdventureMovementComponent)
	{
		AdventureMovementComponent->RequestHopping();
	}
}

void AAdventurePlayerCharacter::OnPlayerEnterClimbState()
{
	if (AAdventurePlayerController* PlayerController = Cast<AAdventurePlayerController>(GetController()))
	{
		PlayerController->AddClimbMappingContext();
	}
}

void AAdventurePlayerCharacter::OnPlayerExitClimbState()
{
	if (AAdventurePlayerController* PlayerController = Cast<AAdventurePlayerController>(GetController()))
	{
		PlayerController->RemoveClimbMappingContext();
	}
}