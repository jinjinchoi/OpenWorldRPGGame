// Cypie

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AdventurePlayerController.generated.h"

class UControllableCharacterManager;
class UAdventureAbilitySystemComponent;
class UInputMappingContext;
struct FInputActionValue;
class UDataAsset_InputConfig;
class UDamageTextComponent;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventurePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void ShowDamageNumber(const float DamageAmount, ACharacter* TargetCharacter, const bool bIsCriticalHit, const FGameplayTag& DamageType);
	void AddClimbMappingContext() const;
	void RemoveClimbMappingContext() const;
	
	UPROPERTY()
	TObjectPtr<UControllableCharacterManager> ControllableCharacterManager;

	void AddDefaultCharacterToManager(ACharacter* CharacterToAdd) const;

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UDataAsset_InputConfig> InputConfigDataAsset;


private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextClass;

#pragma region Input Binding Functions
	
	void Input_Look(const FInputActionValue& InputActionValue);
	void Input_CameraScroll(const FInputActionValue& InputActionValue);
	
	void Input_Jump();
	void Input_Run(const FInputActionValue& InputActionValue);
	void Input_Walk();
	void Input_Sprint_Started();
	void Input_Sprint_Completed();
	void Input_StopMove();
	
	void Input_AbilityInputPressed(FGameplayTag InInputTag);
	void Input_AbilityInputReleased(FGameplayTag InInputTag);

	void Input_ClimbMovement(const FInputActionValue& InputActionValue);
	void Input_ClimbActionCompleted();
	void Input_ClimbHopActionStarted(const FInputActionValue& InputActionValue);

	void AddInputMappingContext(const UInputMappingContext* MappingContext, const int32 InPriority) const;
	void RemoveInputMappingContext(const UInputMappingContext* MappingContext) const;
	
#pragma endregion
	
};
