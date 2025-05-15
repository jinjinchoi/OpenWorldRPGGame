// Copyright Choi JinWoo. All Rights Reserved.


#include "Actor/Camera/AdventurePlayerCamera.h"

#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"


AAdventurePlayerCamera::AAdventurePlayerCamera()
{

	PrimaryActorTick.bCanEverTick = true;
	PrimaryActorTick.TickInterval = 0.033f;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm"));
	CameraBoom->SetupAttachment(Root);
	CameraBoom->TargetArmLength = TargetArmLength;
	CameraBoom->SetRelativeLocation(FVector(0.f, 0.f, 30.f));
	
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);

	FollowTarget = nullptr;

}


void AAdventurePlayerCamera::BeginPlay()
{
	Super::BeginPlay();
	
}


void AAdventurePlayerCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	
	if (FollowTarget)
	{
		TargetLocation = FollowTarget->GetComponentLocation();
		SetActorLocation(TargetLocation);
	
	}
	if (PlayerController)
	{
		FRotator ControllerRotation = PlayerController->GetControlRotation();
		ControllerRotation.Roll = 0.f;    
		SetActorRotation(ControllerRotation);
	}

}

void AAdventurePlayerCamera::SetFollowTarget(USceneComponent* NewTarget)
{
	FollowTarget = NewTarget;
	if (FollowTarget)
	{
		TargetLocation = FollowTarget->GetComponentLocation();
	}
}

void AAdventurePlayerCamera::CameraScroll(const float InputValue)
{
	const float ScrollValue = InputValue * -CameraZoomSpeed;
	const float NewTargetArmLength =  CameraBoom->TargetArmLength + ScrollValue;
	
	TargetArmLength = FMath::Clamp(NewTargetArmLength, MinZoom, MaxZoom);

	if (!bIsZooming)
	{
		StartZoomInterp();
	}
}

void AAdventurePlayerCamera::StartZoomInterp()
{
	bIsZooming = true;
	GetWorld()->GetTimerManager().SetTimer(ZoomInterpTimerHandle, this, &AAdventurePlayerCamera::ZoomInterpTick, 0.016f, true);
}

void AAdventurePlayerCamera::ZoomInterpTick()
{
	const float CurrentLength = CameraBoom->TargetArmLength;
	const float NewLength = FMath::FInterpTo(CurrentLength, TargetArmLength, GetWorld()->GetDeltaSeconds(), ZoomInterpSpeed);

	CameraBoom->TargetArmLength = NewLength;

	if (FMath::IsNearlyEqual(NewLength, TargetArmLength, 0.5f))
	{
		CameraBoom->TargetArmLength = TargetArmLength;
		GetWorld()->GetTimerManager().ClearTimer(ZoomInterpTimerHandle);
		bIsZooming = false;
	}
}