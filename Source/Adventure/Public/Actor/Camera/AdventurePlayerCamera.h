// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AdventurePlayerCamera.generated.h"

class USpringArmComponent;
class UCameraComponent;

UCLASS()
class ADVENTURE_API AAdventurePlayerCamera : public AActor
{
	GENERATED_BODY()
	
public:	
	AAdventurePlayerCamera();
	virtual void Tick(float DeltaTime) override;

	void SetFollowTarget(USceneComponent* NewTarget);
	
	void CameraScroll(const float InputValue);

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USceneComponent> Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UCameraComponent> FollowCamera;
	
	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<USceneComponent> FollowTarget;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(ClampMin="0.0"))
	float CameraZoomSpeed = 100.f;

	UPROPERTY(EditAnywhere, Category="Camera Zoom")
	float ZoomInterpSpeed = 7.5f;

	UPROPERTY(EditAnywhere, Category="Camera Zoom")
	float MinZoom = 200.f;

	UPROPERTY(EditAnywhere, Category="Camera Zoom")
	float MaxZoom = 800.f;
	
	FTimerHandle ZoomInterpTimerHandle;
	float TargetArmLength = 500.f;
	bool bIsZooming = false;

private:
	void StartZoomInterp();
	void ZoomInterpTick();
	
	FVector TargetLocation;
	FRotator ControlRotation;
	
	UPROPERTY()
	TObjectPtr<APlayerController> PlayerController;

public:
	FORCEINLINE void SetPlayerController(APlayerController* NewPlayerController) { PlayerController = NewPlayerController; }

};
