// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

struct FInputActionValue;

// This class does not need to be modified.
UINTERFACE(MinimalAPI)
class UPlayerInterface : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class ADVENTURE_API IPlayerInterface
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void ShowWeaponMesh();

	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
	void HideWeaponMesh();

	// Input
	virtual void Input_Look(const FInputActionValue& InputActionValue) = 0;
	virtual void Input_CameraScroll(const FInputActionValue& InputActionValue) = 0;
	
	virtual void Input_Jump() = 0;
	virtual void Input_Move(const FInputActionValue& InputActionValue) = 0;
	virtual void Input_Walk() = 0;
	virtual void Input_Sprint_Started() = 0;
	virtual void Input_Sprint_Completed() = 0;
	virtual void Input_StopMove() = 0;
	
	virtual void Input_ClimbMovement(const FInputActionValue& InputActionValue) = 0;
	virtual void Input_ClimbActionCompleted() = 0;
	virtual void Input_ClimbHopActionStarted(const FInputActionValue& InputActionValue) = 0;
	
};
