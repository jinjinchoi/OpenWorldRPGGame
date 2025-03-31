// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Character/AdventureBaseCharacter.h"
#include "Interface/PlayerInterface.h"
#include "AdventurePlayerCharacter.generated.h"

struct FInputActionValue;
class UDataAsset_InputConfig;
class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventurePlayerCharacter : public AAdventureBaseCharacter, public IPlayerInterface
{
	GENERATED_BODY()

public:
	AAdventurePlayerCharacter();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

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
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<UCameraComponent> FollowCamera;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = Camera)
	TObjectPtr<USpringArmComponent> CameraBoom;
	
#pragma endregion

#pragma region Input

	/* 카메라 스크롤 속도 */
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category=Input, meta=(ClampMin="0.0"))
	float CameraZoomSpeed = 300;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UDataAsset_InputConfig> InputConfigDataAsset;

	virtual void Jump() override;
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_CameraScroll(const FInputActionValue& InputActionValue);
	
	void Input_Move(const FInputActionValue& InputActionValue);
	void StopMove();
	
	void Input_Sprint_Started();
	void Input_Sprint_Completed();
	void StartSprint();
	void StopSprint();
	bool bIsSprint = false;
	bool bIsWalking = false;
	FTimerHandle SprintTimerHandle;
	
	void Input_Walk();

	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);
	
	
#pragma endregion

	UFUNCTION(BlueprintImplementableEvent)
	void SetWeaponMeshVisibility(bool bIsVisible);
	
private:
	
	
};
