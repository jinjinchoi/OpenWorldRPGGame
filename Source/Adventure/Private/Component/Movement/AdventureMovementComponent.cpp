// Copyright Choi JinWoo. All Rights Reserved.


#include "Component/Movement/AdventureMovementComponent.h"
#include "MotionWarpingComponent.h"
#include "AdventureType/AdventureEnumTypes.h"
#include "Character/AdventureBaseCharacter.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/Character.h"
#include "Kismet/KismetMathLibrary.h"
#include "Kismet/KismetSystemLibrary.h"

void UAdventureMovementComponent::BeginPlay()
{
	Super::BeginPlay();

	OwningPlayerAnimInstance = CharacterOwner->GetMesh()->GetAnimInstance();
	if (OwningPlayerAnimInstance)
	{
		OwningPlayerAnimInstance->OnMontageEnded.AddDynamic(this, &UAdventureMovementComponent::OnClimbMontageEnded);
		OwningPlayerAnimInstance->OnMontageBlendingOut.AddDynamic(this, &UAdventureMovementComponent::OnClimbMontageEnded);
	}

	OwningPlayerCharacter = Cast<AAdventureBaseCharacter>(CharacterOwner);
	
	if (CachedOwnerCapsuleHalfHeight == 0)
	{
		CachedOwnerCapsuleHalfHeight = CharacterOwner->GetCapsuleComponent()->GetUnscaledCapsuleHalfHeight();
	}
	
}


void UAdventureMovementComponent::OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode)
{
	if (IsClimbing())
	{
		bOrientRotationToMovement = false;
		CharacterOwner->GetCapsuleComponent()->SetCapsuleHalfHeight(CachedOwnerCapsuleHalfHeight * 0.8);

		OnEnterClimbStateDelegate.ExecuteIfBound();
	}

	if (PreviousMovementMode == MOVE_Custom && PreviousCustomMode == ECustomMovementMode::MOVE_Climb)
	{
		bOrientRotationToMovement = true;
		CharacterOwner->GetCapsuleComponent()->SetCapsuleHalfHeight(CachedOwnerCapsuleHalfHeight);

		const FRotator DirtyRotation = UpdatedComponent->GetComponentRotation();
		const FRotator CleanStandRotation = FRotator(0.f, DirtyRotation.Yaw, 0.f);
		UpdatedComponent->SetRelativeRotation(CleanStandRotation);
		
		StopMovementImmediately();
		
		OnExitClimbStateDelegate.ExecuteIfBound();
	}
	
	Super::OnMovementModeChanged(PreviousMovementMode, PreviousCustomMode);
}

void UAdventureMovementComponent::PhysCustom(float deltaTime, int32 Iterations)
{
	Super::PhysCustom(deltaTime, Iterations);

	if (IsClimbing())
	{
		PhysClimb(deltaTime, Iterations);
	}
}

float UAdventureMovementComponent::GetMaxSpeed() const
{
	if (IsClimbing())
	{
		return MaxClimbSpeed;
	}
	else
	{
		return Super::GetMaxSpeed();
	}
}

float UAdventureMovementComponent::GetMaxAcceleration() const
{
	if (IsClimbing())
	{
		return MaxClimbAcceleration;
	}
	else
	{
		return Super::GetMaxAcceleration();
	}
}

FVector UAdventureMovementComponent::ConstrainAnimRootMotionVelocity(const FVector& RootMotionVelocity, const FVector& CurrentVelocity) const
{
	if (IsFalling() && OwningPlayerAnimInstance && OwningPlayerAnimInstance->IsAnyMontagePlaying())
	{
		return RootMotionVelocity;
	}
	else
	{
		return Super::ConstrainAnimRootMotionVelocity(RootMotionVelocity, CurrentVelocity);
	}
}

TArray<FHitResult> UAdventureMovementComponent::DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End)
{
	TArray<FHitResult> OutCapsuleTraceHitResults;
	
	UKismetSystemLibrary::CapsuleTraceMultiForObjects(
		this,
		Start,
		End,
		ClimbCapsuleTraceRadius,
		ClimbCapsuleTraceHalfHeight,
		ClimbableSurfaceTraceTypes,
		false,
		TArray<AActor*>(),
		bShowDebugShape ? EDrawDebugTrace::ForOneFrame: EDrawDebugTrace::None,
		OutCapsuleTraceHitResults,
		true
	);

	return OutCapsuleTraceHitResults;
	
}

FHitResult UAdventureMovementComponent::DoLineTraceSingleByObject(const FVector& Start, const FVector& End)
{
	FHitResult OutHit;
	
	UKismetSystemLibrary::LineTraceSingleForObjects(
		this,
		Start,
		End,
		ClimbableSurfaceTraceTypes,
		false,
		TArray<AActor*>(),
		bShowDebugShape ? EDrawDebugTrace::ForOneFrame: EDrawDebugTrace::None,
		OutHit,
		true
	);

	return OutHit;
}

// 등반 가능한 표면 트레이스. return true == 등반가능한 표면이 존재함
bool UAdventureMovementComponent::TraceClimbableSurfaces()
{
	const FVector StartOffset = UpdatedComponent->GetForwardVector() * 30.f; 
	const FVector Start = UpdatedComponent->GetComponentLocation() + StartOffset;
	const FVector End = Start + UpdatedComponent->GetForwardVector();
	ClimbableSurfacesTracedResults = DoCapsuleTraceMultiByObject(Start, End);

	return !ClimbableSurfacesTracedResults.IsEmpty();
}

FHitResult UAdventureMovementComponent::TraceFromEyeHeight(const float TraceDistance, const float TraceStartOffset)
{
	const FVector ComponentLocation = UpdatedComponent->GetComponentLocation();
	const FVector ForwardVector = UpdatedComponent->GetComponentRotation().Vector().GetSafeNormal();
	const FVector UpVector = FVector::UpVector; // 월드 기준
	
	const FVector EyeHeightOffset = UpVector * (CharacterOwner->BaseEyeHeight + TraceStartOffset);

	const FVector Start = ComponentLocation + EyeHeightOffset;
	const FVector End = Start + ForwardVector * TraceDistance;

	return DoLineTraceSingleByObject(Start, End);
	
}



bool UAdventureMovementComponent::IsClimbing() const
{
	return MovementMode == MOVE_Custom && CustomMovementMode == ECustomMovementMode::MOVE_Climb;
}



bool UAdventureMovementComponent::CanStartClimbing()
{
	if (IsFalling()) return false;
	if (!TraceClimbableSurfaces()) return false;
	if (!TraceFromEyeHeight(100.f).bBlockingHit) return false;
	if (!TraceFromEyeHeight(100.f, MountTraceOffset).bBlockingHit) return false;

	return true;
	
}


void UAdventureMovementComponent::StartClimbing()
{
	SetMovementMode(MOVE_Custom, ECustomMovementMode::MOVE_Climb);
}

void UAdventureMovementComponent::StopClimbing()
{
	SetMovementMode(MOVE_Falling);
}

void UAdventureMovementComponent::PhysClimb(float deltaTime, int32 Iterations)
{
	if (deltaTime < MIN_TICK_TIME)
	{
		return;
	}

	/* Process all the climbable surfaces info */
	TraceClimbableSurfaces();
	ProcessClimbableSurfaceInfo();
	
	/* Check if we should stop climbing */
	if (CheckShouldStopClimbing() || CheckHasReachedFloor())
	{
		StopClimbing();
	} 
	RestorePreAdditiveRootMotionVelocity();

	if( !HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity() )
	{
		// Define the Max climb speed and acceleration
		CalcVelocity(deltaTime, 0.f, true, MaxBreakClimbDeceleration);
	}

	ApplyRootMotionToVelocity(deltaTime);

	FVector OldLocation = UpdatedComponent->GetComponentLocation();
	const FVector Adjusted = Velocity * deltaTime;
	FHitResult Hit(1.f);

	// Handle climb rotation
	SafeMoveUpdatedComponent(Adjusted, GetClimbRotation(deltaTime), true, Hit);
	
	if (Hit.Time < 1.f)
	{
		//adjust and try again
		HandleImpact(Hit, deltaTime, Adjusted);
		SlideAlongSurface(Adjusted, (1.f - Hit.Time), Hit.Normal, Hit, true);
	}

	if(!HasAnimRootMotion() && !CurrentRootMotion.HasOverrideVelocity() )
	{
		Velocity = (UpdatedComponent->GetComponentLocation() - OldLocation) / deltaTime;
	}

	/* Snap movement to climbable surface */
	SnapMovementToClimbableSurfaces(deltaTime);
	
	if (CheckHasReachedLedge())
	{
		PlayClimbMontage(ClimbToTopMontage);
	}

}

void UAdventureMovementComponent::ProcessClimbableSurfaceInfo()
{
	CurrentClimbableSurfaceLocation = FVector::ZeroVector;
	CurrentClimbableSurfaceNormal = FVector::ZeroVector;

	if (ClimbableSurfacesTracedResults.IsEmpty()) return;

	for (const FHitResult& TraceHitResult : ClimbableSurfacesTracedResults)
	{
		CurrentClimbableSurfaceLocation += TraceHitResult.ImpactPoint;
		CurrentClimbableSurfaceNormal += TraceHitResult.ImpactNormal;
	}

	CurrentClimbableSurfaceLocation /= ClimbableSurfacesTracedResults.Num();
	CurrentClimbableSurfaceNormal = CurrentClimbableSurfaceNormal.GetSafeNormal();
	
}

bool UAdventureMovementComponent::CheckShouldStopClimbing()
{
	if (ClimbableSurfacesTracedResults.IsEmpty()) return true;

	const float DotResult = FVector::DotProduct(CurrentClimbableSurfaceNormal, FVector::UpVector);
	const float DegreeDiff = FMath::RadiansToDegrees(FMath::Acos(DotResult));

	if (DegreeDiff <= 60.f)
	{
		return true;
	}
	
	return false;
	
}

bool UAdventureMovementComponent::CheckHasReachedFloor()
{
	const FVector DownVector = -UpdatedComponent->GetUpVector();
	const FVector StartOffset = DownVector * 50.f;
	const FVector Start = UpdatedComponent->GetComponentLocation() + StartOffset;
	const FVector End = Start + DownVector;

	TArray<FHitResult> PossibleFloorHits = DoCapsuleTraceMultiByObject(Start, End);

	if (PossibleFloorHits.IsEmpty()) return false;

	for (const FHitResult& PossibleFloorHit : PossibleFloorHits)
	{
		return FVector::Parallel(-PossibleFloorHit.ImpactNormal, FVector::UpVector) && GetUnRotatedClimbVelocity().Z < -10.f;
	}

	return false;
}


FQuat UAdventureMovementComponent::GetClimbRotation(float DeltaTime) const
{
	const FQuat CurrentQuat = UpdatedComponent->GetComponentQuat();

	if (HasAnimRootMotion() || CurrentRootMotion.HasOverrideVelocity())
	{
		return CurrentQuat;
	}

	const FQuat TargetQuat = FRotationMatrix::MakeFromX(-CurrentClimbableSurfaceNormal).ToQuat();

	return FMath::QInterpTo(CurrentQuat, TargetQuat, DeltaTime, 5.f);
	
}

void UAdventureMovementComponent::SnapMovementToClimbableSurfaces(float DeltaTime)
{
	const FVector ComponentForward = UpdatedComponent->GetForwardVector();
	const FVector ComponentLocation = UpdatedComponent->GetComponentLocation();

	const FVector ProjectedCharacterToSurface = (CurrentClimbableSurfaceLocation - ComponentLocation).ProjectOnTo(ComponentForward);

	const FVector SnapVector = -CurrentClimbableSurfaceNormal * ProjectedCharacterToSurface.Length();

	UpdatedComponent->MoveComponent(
		SnapVector * DeltaTime * MaxClimbSpeed,
		UpdatedComponent->GetComponentQuat(),
		true
	);
	
}

bool UAdventureMovementComponent::CheckHasReachedLedge()
{
	FHitResult LedgeHitResult = TraceFromEyeHeight(100.f, 25.f);
	
	if (!LedgeHitResult.bBlockingHit)
	{
		const FVector WalkableSurfaceTraceStart = LedgeHitResult.TraceEnd;
		const FVector DownVector = -UpdatedComponent->GetUpVector();
		const FVector WalkableSurfaceTraceEnd = WalkableSurfaceTraceStart + DownVector * 100.f;
	
		FHitResult WalkableSurfaceHitResult = DoLineTraceSingleByObject(WalkableSurfaceTraceStart, WalkableSurfaceTraceEnd);
		if (WalkableSurfaceHitResult.bBlockingHit && GetUnRotatedClimbVelocity().Z > 10.f)
		{
			SetMotionWarpTarget(FName("ClimbUpTarget"), WalkableSurfaceHitResult.ImpactPoint);
			return true;
		}
	}
	
	return false;
	
}

void UAdventureMovementComponent::TryStartMounting()
{
	FHitResult LedgeHitResult = TraceFromEyeHeight(50.f, MountTraceOffset);

	if (!LedgeHitResult.bBlockingHit)
	{
		const FVector WalkableSurfaceTraceStart = LedgeHitResult.TraceEnd;
		const FVector DownVector = -UpdatedComponent->GetUpVector();
		const FVector WalkableSurfaceTraceEnd = WalkableSurfaceTraceStart + DownVector * MountTraceOffset;

		FHitResult WalkableSurfaceHitResult = DoLineTraceSingleByObject(WalkableSurfaceTraceStart, WalkableSurfaceTraceEnd);
		if (WalkableSurfaceHitResult.bBlockingHit)
		{
			SetMotionWarpTarget(FName("MountStartPoint"), WalkableSurfaceHitResult.ImpactPoint);
			StartClimbing();
			PlayClimbMontage(MountMontage);
			
		}
	}	
}

bool UAdventureMovementComponent::CanStartMounting()
{
	if (IsFalling()) return false;
	if (!TraceClimbableSurfaces()) return false;
	if (!TraceFromEyeHeight(100.f).bBlockingHit) return false;
	if (TraceFromEyeHeight(100.f, MountTraceOffset).bBlockingHit) return false;

	return true;
}

void UAdventureMovementComponent::TtyStartValuting()
{
	FVector ValultStartPosition;
	FVector ValultLandPosition;
	if (CanStartValuting(ValultStartPosition, ValultLandPosition))
	{
		SetMotionWarpTarget(FName("ValutStartPoint"), ValultStartPosition);
		SetMotionWarpTarget(FName("ValutLandPoint"), ValultLandPosition);

		StartClimbing();
		PlayClimbMontage(ValutMontage);
	}
}

bool UAdventureMovementComponent::CanStartValuting(FVector& OutValutStartPosition, FVector& OutValutLandPosition)
{
	if (IsFalling()) return false;

	OutValutStartPosition = FVector::ZeroVector;
	OutValutLandPosition = FVector::ZeroVector;

	const FVector ComponentLocation = UpdatedComponent->GetComponentLocation();
	const FVector ComponentForward = UpdatedComponent->GetForwardVector();
	const FVector UpVector = UpdatedComponent->GetUpVector();
	const FVector DownVector = -UpdatedComponent->GetUpVector();

	const FVector FrontStart = ComponentLocation + UpVector * 50.f + ComponentForward * 50.f;
	const FVector FrontEnd = FrontStart + DownVector * 100.f;

	const FVector BackStart = FrontStart + ComponentForward * 50.f;
	const FVector BackEnd = BackStart + DownVector * 200.f;

	const FHitResult FrontTraceHit = DoLineTraceSingleByObject(FrontStart, FrontEnd);
	const FHitResult BackTraceHit = DoLineTraceSingleByObject(BackStart, BackEnd);

	if (FrontTraceHit.bBlockingHit && BackTraceHit.bBlockingHit)
	{
		OutValutStartPosition = FrontTraceHit.ImpactPoint + ComponentForward * 30.f;
		OutValutLandPosition = BackTraceHit.ImpactPoint;
		return true;
	}
	
	return false;
	
}

void UAdventureMovementComponent::PlayClimbMontage(UAnimMontage* MontageToPlay)
{
	if (!MontageToPlay) return;
	if (!OwningPlayerAnimInstance) return;
	if (OwningPlayerAnimInstance->IsAnyMontagePlaying()) return;
	
	OwningPlayerAnimInstance->Montage_Play(MontageToPlay);
	
}

void UAdventureMovementComponent::OnClimbMontageEnded(UAnimMontage* Montage, bool bInterrupted)
{
	if (Montage == IdleToClimbMontage)
	{
		StartClimbing();
	}
	else if (Montage == ClimbToTopMontage)
	{
		SetMovementMode(MOVE_Walking);
	}

}

void UAdventureMovementComponent::SetMotionWarpTarget(const FName& InWarpTargetName, const FVector& InTargetPosition)
{
	if (!OwningPlayerCharacter) return;

	OwningPlayerCharacter->GetMotionWarpingComponent()->AddOrUpdateWarpTargetFromLocation(InWarpTargetName, InTargetPosition);
	
}

void UAdventureMovementComponent::HandleHopUp()
{
	FVector HopUpTargetPoint;
	
	if (CheckCanHopUp(HopUpTargetPoint))
	{
		SetMotionWarpTarget(FName("HopUpTargetPoint"), HopUpTargetPoint);
		PlayClimbMontage(HopUpMontage);
	}
}

bool UAdventureMovementComponent::CheckCanHopUp(FVector& OutHopUpTargetPosition)
{
	const FHitResult HopUpHit = TraceFromEyeHeight(100.f, HopRange);
	const FHitResult SafetyLedgeHit = TraceFromEyeHeight(100.f, SafetyHopRange);

	if (HopUpHit.bBlockingHit && SafetyLedgeHit.bBlockingHit)
	{
		OutHopUpTargetPosition = HopUpHit.ImpactPoint;
		return true;
	}

	return false;
}

void UAdventureMovementComponent::HandleHopRight()
{
	FVector HopRightTracePoint;

	if (CanHopLeftOrRight(HopRightTracePoint, false))
	{
		SetMotionWarpTarget(FName("HopRightTargetPoint"), HopRightTracePoint);
		DrawDebugPoint(GetWorld(), HopRightTracePoint, 5.f, FColor::Yellow, false, 6);
		PlayClimbMontage(HopRightMontage);
	}
	
}



void UAdventureMovementComponent::HandleHopLeft()
{
	FVector HopLeftTracePoint;

	if (CanHopLeftOrRight(HopLeftTracePoint, true))
	{
		SetMotionWarpTarget(FName("HopLeftTargetPoint"), HopLeftTracePoint);
		DrawDebugPoint(GetWorld(), HopLeftTracePoint, 5.f, FColor::Yellow, false, 6);
		PlayClimbMontage(HopLeftMontage);
	}
}



bool UAdventureMovementComponent::CanHopLeftOrRight(FVector& OutHopRightTargetPosition, const bool IsLeft)
{
	const FVector CenterLocation = UpdatedComponent->GetComponentLocation() - FVector(0.f, 0.f, CachedOwnerCapsuleHalfHeight * 0.9);
	const FVector ComponentForward = UpdatedComponent->GetForwardVector();
	const FVector TransverseVector = IsLeft ? -UpdatedComponent->GetRightVector() : UpdatedComponent->GetRightVector();

	const FVector TraceStart = CenterLocation + TransverseVector * HopRange;
	const FVector TraceEnd = TraceStart + ComponentForward * 100.f;

	const FVector SafetyTraceStart = CenterLocation + TransverseVector * SafetyHopRange;
	const FVector SafetyTraceEnd = TraceStart + ComponentForward * 100.f;

	const FHitResult HopHit = DoLineTraceSingleByObject(TraceStart, TraceEnd);
	const FHitResult SafetyHopLeftHit = DoLineTraceSingleByObject(SafetyTraceStart, SafetyTraceEnd);

	if (HopHit.bBlockingHit && SafetyHopLeftHit.bBlockingHit)
	{
		OutHopRightTargetPosition = HopHit.ImpactPoint;
		return true;
	}

	return false;
}


FVector UAdventureMovementComponent::GetUnRotatedClimbVelocity() const
{
	return UKismetMathLibrary::Quat_UnrotateVector(UpdatedComponent->GetComponentQuat(), Velocity);
}

void UAdventureMovementComponent::RequestHopping()
{
	const FVector UnRotatedLastInputVector = UKismetMathLibrary::Quat_UnrotateVector(UpdatedComponent->GetComponentQuat(), GetLastInputVector());

	const float UpVectorDotResult = FVector::DotProduct(UnRotatedLastInputVector.GetSafeNormal(), FVector::UpVector);
	const float RightVectorDotResult = FVector::DotProduct(UnRotatedLastInputVector.GetSafeNormal(), FVector::RightVector);

	if (UpVectorDotResult >= 0.9)
	{
		HandleHopUp();
	}
	else if (UpVectorDotResult <= -0.9)
	{
		PlayClimbMontage(WallDownMontage);
		StopClimbing();
	}
	else if (RightVectorDotResult >= 0.9)
	{
		HandleHopRight();
	}
	else if (RightVectorDotResult <= -0.9)
	{
		HandleHopLeft();
	}
	
}


void UAdventureMovementComponent::ToggleClimbing(bool bEnableClimb, bool& OutbIsClimbStated)
{
	OutbIsClimbStated = false;
	
	if (bEnableClimb)
	{
		if (CanStartClimbing())
		{
			PlayClimbMontage(IdleToClimbMontage);
			OutbIsClimbStated = true;
		}
		else if (CanStartMounting())
		{
			TryStartMounting();
		}
		else
		{
			TtyStartValuting();
		}
	}
	else
	{
		StopClimbing();
	}
}