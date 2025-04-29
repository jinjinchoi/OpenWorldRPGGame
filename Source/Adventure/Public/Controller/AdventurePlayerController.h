// Cypie

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "GenericTeamAgentInterface.h"
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
class ADVENTURE_API AAdventurePlayerController : public APlayerController, public IGenericTeamAgentInterface
{
	GENERATED_BODY()

public:
	AAdventurePlayerController();
	
	void ShowDamageNumber(const float DamageAmount, ACharacter* TargetCharacter, const bool bIsCriticalHit, const FGameplayTag& DamageType);
	void AddClimbMappingContext() const;
	void RemoveClimbMappingContext() const;

	/* Begin IGenericTeamAgentInterface Interface.*/
	virtual FGenericTeamId GetGenericTeamId() const override;
	/* End IGenericTeamAgentInterface Interface. */

protected:
	virtual void BeginPlay() override;
	virtual void SetupInputComponent() override;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = Input)
	TObjectPtr<UDataAsset_InputConfig> InputConfigDataAsset;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="UI")
	TSubclassOf<UUserWidget> MenuWidgetClass;
	
	UPROPERTY()
	TObjectPtr<UUserWidget> MenuWidget;


private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextClass;

	FGenericTeamId HeroTeamId;

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

	void Input_ChangeCharacter_One();
	void Input_ChangeCharacter_Two();
	void Input_ChangeCharacter_Three();

	void Input_Interaction();
	void Input_OpenMenu();
	
#pragma endregion
	
};
