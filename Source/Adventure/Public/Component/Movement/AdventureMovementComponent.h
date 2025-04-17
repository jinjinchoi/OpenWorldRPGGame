// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AdventureMovementComponent.generated.h"

DECLARE_DELEGATE(FOnEnterClimbState);
DECLARE_DELEGATE(FOnExitClimbState);


class AAdventureBaseCharacter;
/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

public:
	FOnEnterClimbState OnEnterClimbStateDelegate;
	FOnExitClimbState OnExitClimbStateDelegate;
	
protected:
	UPROPERTY(EditDefaultsOnly, Category="Debug")
	bool bShowDebugShape = false;

#pragma region OverridenFunctions

	virtual void BeginPlay() override;
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	virtual float GetMaxSpeed() const override;
	virtual float GetMaxAcceleration() const override;
	virtual FVector ConstrainAnimRootMotionVelocity(const FVector& RootMotionVelocity, const FVector& CurrentVelocity) const override;
	
	
#pragma endregion 
	
private:
	
#pragma region ClimbTraces

	TArray<FHitResult> DoCapsuleTraceMultiByObject(const FVector& Start, const FVector& End);
	FHitResult DoLineTraceSingleByObject(const FVector& Start, const FVector& End);
	
#pragma endregion

#pragma region ClimbCore
	
	bool TraceClimbableSurfaces();
	FHitResult TraceFromEyeHeight(const float TraceDistance, const float TraceStartOffset = 0.f);
	bool CanStartClimbing();
	void StartClimbing();
	void StopClimbing();
	void PhysClimb(float deltaTime, int32 Iterations);
	void ProcessClimbableSurfaceInfo();
	bool CheckShouldStopClimbing();
	bool CheckHasReachedFloor();
	FQuat GetClimbRotation(float DeltaTime) const;
	void SnapMovementToClimbableSurfaces(float DeltaTime);
	bool CheckHasReachedLedge();
	void TryStartMounting();
	bool CanStartMounting();
	void TtyStartValuting();
	bool CanStartValuting(FVector& OutValutStartPosition, FVector& OutValutLandPosition);
	void PlayClimbMontage(UAnimMontage* MontageToPlay);

	UFUNCTION()
	void OnClimbMontageEnded(UAnimMontage* Montage, bool bInterrupted);

	void SetMotionWarpTarget(const FName& InWarpTargetName, const FVector& InTargetPosition);

	void HandleHopUp();
	bool CheckCanHopUp(FVector& OutHopUpTargetPosition);
	void HandleHopRight();
	bool CheckCanHopRight(FVector& OutHopRightTargetPosition);
	void HandleHopLeft();
	bool CheckCanHopLeft(FVector& OutHopRightTargetPosition);
	bool CanHopLeftOrRight(FVector& OutHopRightTargetPosition, const bool IsLeft);

	
#pragma endregion

#pragma region ClimbCoreVariables

	float CachedOwnerCapsuleHalfHeight = 0.f;
	TArray<FHitResult> ClimbableSurfacesTracedResults;
	FVector CurrentClimbableSurfaceLocation;
	FVector CurrentClimbableSurfaceNormal;

	UPROPERTY()
	TObjectPtr<UAnimInstance> OwningPlayerAnimInstance;

	UPROPERTY()
	TObjectPtr<AAdventureBaseCharacter> OwningPlayerCharacter;
	
#pragma endregion 
	
#pragma region ClimbBPVariables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	TArray<TEnumAsByte<EObjectTypeQuery>> ClimbableSurfaceTraceTypes;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	float ClimbCapsuleTraceRadius = 40.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	float ClimbCapsuleTraceHalfHeight = 72.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	float MaxBreakClimbDeceleration = 600.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	float MaxClimbSpeed = 100.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	float MaxClimbAcceleration = 400.f;

	/* Climb과 Mount을 구분할 기준 높이 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	float MountTraceOffset = 150.f;

	/* Hop으로 갈 거리 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	float HopRange = 100;

	/* Hop 안전 확인 범위 */
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	float SafetyHopRange = 150;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> IdleToClimbMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> ClimbToTopMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> MountMontage;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> ValutMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> HopUpMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> HopLeftMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> HopRightMontage;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	TObjectPtr<UAnimMontage> WallDownMontage;
	
#pragma endregion

	
public:
	
	void ToggleClimbing(bool bEnableClimb, bool& OutbIsClimbStated);
	bool IsClimbing() const;
	void RequestHopping();
	
	FORCEINLINE void SetCapsuleComponentHalfHeight(const float InCapsuleHalfHeight) { CachedOwnerCapsuleHalfHeight = InCapsuleHalfHeight; }
	FORCEINLINE FVector GetClimbableSurfaceNormal() const { return CurrentClimbableSurfaceNormal; }
	FVector GetUnRotatedClimbVelocity() const;
	
};
