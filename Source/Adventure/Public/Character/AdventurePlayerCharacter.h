// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/AdventureBaseCharacter.h"
#include "AdventurePlayerCharacter.generated.h"

struct FInputActionValue;
class UDataAsset_InputConfig;
class USpringArmComponent;
class UCameraComponent;
/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventurePlayerCharacter : public AAdventureBaseCharacter
{
	GENERATED_BODY()

public:
	AAdventurePlayerCharacter();
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	float WalkingSpeed = 200.f;

	/** 별다른 조작없이 움직이면 기본적으론 Run 상태 **/
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
	void Input_Sprint();
	void Input_Walk();
	
	bool bIsSprint = false;
	bool bIsWalking = false;
	
#pragma endregion
	
};
