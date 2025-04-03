// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "AdventureMovementComponent.generated.h"



/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureMovementComponent : public UCharacterMovementComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditDefaultsOnly, Category="Debug")
	bool bShowDebugShape = false;

#pragma region OverridenFunctions
	
	virtual void OnMovementModeChanged(EMovementMode PreviousMovementMode, uint8 PreviousCustomMode) override;
	virtual void PhysCustom(float deltaTime, int32 Iterations) override;
	virtual float GetMaxSpeed() const override;
	virtual float GetMaxAcceleration() const override;
	
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
	FQuat GetClimbRotation(float DeltaTime) const;
	void SnapMovementToClimbableSurfaces(float DeltaTime);

	
#pragma endregion

#pragma region ClimbCoreVariables

	TArray<FHitResult> ClimbableSurfacesTracedResults;
	FVector CurrentClimbableSurfaceLocation;
	FVector CurrentClimbableSurfaceNormal;
	
#pragma endregion 
	
#pragma region ClimbBPVariables

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	TArray<TEnumAsByte<EObjectTypeQuery>> ClimbableSurfaceTraceTypes;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	float ClimbCapsuleTraceRadius = 50.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	float ClimbCapsuleTraceHalfHeight = 72.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	float MaxBreakClimbDeceleration = 600.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	float MaxClimbSpeed = 150.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Movement : Climbing", meta=(AllowPrivateAccess=true))
	float MaxClimbAcceleration = 400.f;

#pragma endregion

#pragma region OnwerVariables
	float CachedOwnerCapsuleHalfHeight = 0.f;
	
#pragma endregion
	
public:
	
	void ToggleClimbing(bool bEnableClimb);
	bool IsClimbing() const;
	
	FORCEINLINE void SetCapsuleComponentHalfHeight(const float InCapsuleHalfHeight) { CachedOwnerCapsuleHalfHeight = InCapsuleHalfHeight; }
	FORCEINLINE FVector GetClimbableSurfaceNormal() const { return CurrentClimbableSurfaceNormal; }
	
};
