// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "PlayerInterface.generated.h"

class AAdventureInventoryItem;
struct FGameplayTag;
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

	virtual void OnStaminaDepleted() = 0;
	virtual void PickUpItemBeginOverlap(AAdventureInventoryItem* InOverlappedItem) = 0;
	virtual void PickUpItemEndOverlap(AAdventureInventoryItem* InOverlappedItem) = 0;

	virtual void ForceCharacterChange(const int32 IndexToChange) = 0;
	virtual void ChangeCharacterPartyIndex(const int32 IndexToChange) = 0;
	virtual FGameplayTag GetOwningCharacterTag() = 0;

	virtual void AddMoney(int32 MoneyToAdd) = 0;
	virtual void LevelUp(const int32 LevelUpAmount = 1) = 0;
	

#pragma region Input
	virtual void Input_Look(const FInputActionValue& InputActionValue) = 0;
	
	virtual void Input_Jump() = 0;
	virtual void Input_Move(const FInputActionValue& InputActionValue) = 0;
	virtual void Input_Walk() = 0;
	virtual void Input_Sprint_Started() = 0;
	virtual void Input_Sprint_Completed() = 0;
	virtual void Input_StopMove() = 0;
	
	virtual void Input_ClimbMovement(const FInputActionValue& InputActionValue) = 0;
	virtual void Input_ClimbActionCompleted() = 0;
	virtual void Input_ClimbHopActionStarted(const FInputActionValue& InputActionValue) = 0;
	
	virtual void Input_CharacterChange_One() = 0;
	virtual void Input_CharacterChange_Two() = 0;
	virtual void Input_CharacterChange_Three() = 0;

	virtual void Input_AbilityInputPressed(const FGameplayTag& InInputTag) = 0;
	virtual void Input_AbilityInputReleased(const FGameplayTag& InInputTag) = 0;
	
	virtual void Input_Interaction() = 0;
#pragma endregion
	
};
