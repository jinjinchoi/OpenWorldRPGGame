// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Character/AdventureBaseCharacter.h"
#include "Interface/PlayerInterface.h"
#include "AdventurePlayerCharacter.generated.h"

class UAdventureMovementComponent;
struct FInputActionValue;
class UDataAsset_InputConfig;
class USpringArmComponent;
class UCameraComponent;
class UInputMappingContext;
/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventurePlayerCharacter : public AAdventureBaseCharacter, public IPlayerInterface
{
	GENERATED_BODY()

public:
	AAdventurePlayerCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
	virtual void BeginPlay() override;

	/* Begin Player Interface */
	virtual void ShowWeaponMesh_Implementation() override;
	virtual void HideWeaponMesh_Implementation() override;
	/* End Player Interface */

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	float WalkingSpeed = 200.f;

	/** 달리기(기본) 속도 **/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	float RunSpeed = 500.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	float SprintSpeed = 700.f;
	

#pragma region Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Camera")
	TObjectPtr<USpringArmComponent> CameraBoom;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UAdventureMovementComponent> AdventureMovementComponent;
	
#pragma endregion

#pragma region Input

	/* 카메라 스크롤 속도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(ClampMin="0.0"))
	float CameraZoomSpeed = 300;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UDataAsset_InputConfig> InputConfigDataAsset;

	virtual void Input_Jump() override;
	virtual void Input_Look(const FInputActionValue& InputActionValue) override;
	virtual void Input_CameraScroll(const FInputActionValue& InputActionValue) override;
	
	virtual void Input_Move(const FInputActionValue& InputActionValue) override;
	virtual void Input_StopMove() override;
	
	virtual void Input_Sprint_Started() override;
	virtual void Input_Sprint_Completed() override;
	void StartSprint();
	void StopSprint();
	bool bIsSprint = false;
	bool bIsWalking = false;
	FTimerHandle SprintTimerHandle;
	
	virtual void Input_Walk() override;
	
	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);

	/* Climb */
	virtual void Input_ClimbMovement(const FInputActionValue& InputActionValue) override;
	void TryClimbAction();
	virtual void Input_ClimbActionCompleted() override;
	
	virtual void Input_ClimbHopActionStarted(const FInputActionValue& InputActionValue) override;
	
	void OnPlayerEnterClimbState();
	void OnPlayerExitClimbState();

	void AddInputMappingContext(const UInputMappingContext* MappingContext, const int32 InPriority);
	void RemoveInputMappingContext(const UInputMappingContext* MappingContext);
	
	
#pragma endregion

	UFUNCTION(BlueprintImplementableEvent)
	void SetWeaponMeshVisibility(bool bIsVisible);
	
private:

public:
	FORCEINLINE UAdventureMovementComponent* GetAdventureMovementComponent() const { return AdventureMovementComponent; }
	
};
