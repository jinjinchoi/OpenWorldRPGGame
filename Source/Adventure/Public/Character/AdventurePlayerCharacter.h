// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayTagContainer.h"
#include "Character/AdventureBaseCharacter.h"
#include "Interface/PlayerInterface.h"
#include "AdventurePlayerCharacter.generated.h"

DECLARE_DELEGATE_OneParam(FOnMovementModechanged, const ECharacterMovementType /* Movement Type */);

class UGameplayEffect;
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
	virtual void BeginPlay() override;
	
	/* Begin Player Interface */
	virtual void ShowWeaponMesh_Implementation() override;
	virtual void HideWeaponMesh_Implementation() override;
	virtual void OnStaminaDepleted() override;
	/* End Player Interface */

	/* Begin Combat Interface */
	virtual void OnCharacterDied_Implementation() override;
	/* End Combat Interface */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Data")
	int32 CurrentCharacterIndex = 1;

	bool bIsFirstLoading = true;

	FOnMovementModechanged OnMovementModeChangedDelegate;

protected:
	virtual void PossessedBy(AController* NewController) override;
	void InitPlayerStartUpData() const;
	void BindGameplayTagChanged();
	void AddCharacterInfoToManager() const;

	/* Begin Adventure Base Character */
	virtual void OnHitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;
	/* End Adventure Base Character */

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	float WalkingSpeed = 200.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	float RunSpeed = 400.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	float SprintSpeed = 600.f;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category=Movement)
	TObjectPtr<UAnimMontage> RunToStopMontage;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay Effect")
	TSubclassOf<UGameplayEffect> RunAndClimbCostEffectClass;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta=(Categories ="CharacterClass.Player"))
	FGameplayTag CharacterTag;
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetWeaponMeshVisibility(bool bIsVisible);

private:
	bool ApplyStaminaCostEffect(const TSubclassOf<UGameplayEffect>& InEffect);
	void RemoveStaminaCostEffect();

	FActiveGameplayEffectHandle StaminaCostEffectHandle;
	

public:
	FORCEINLINE UAdventureMovementComponent* GetAdventureMovementComponent() const { return AdventureMovementComponent; }
	FORCEINLINE FGameplayTag GetCharacterClassTag() const { return CharacterTag; }
	FORCEINLINE UDataAsset_StartUpDataBase* GetCharacterStartUpData() const { return CharacterStartUpData; }

protected:

		
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
	
	virtual void Input_AbilityInputPressed(const FGameplayTag& InInputTag) override;
	virtual void Input_AbilityInputReleased(const FGameplayTag& InInputTag) override;

	/* Climb */
	virtual void Input_ClimbMovement(const FInputActionValue& InputActionValue) override;
	void TryClimbAction();
	virtual void Input_ClimbActionCompleted() override;
	
	virtual void Input_ClimbHopActionStarted(const FInputActionValue& InputActionValue) override;
	
	void OnPlayerEnterClimbState();
	void OnPlayerExitClimbState();

	/* Character Change */
	virtual void Input_CharacterChange_One() override;
	virtual void Input_CharacterChange_Two() override;
	virtual void Input_CharacterChange_Three() override;
	
	
#pragma endregion
	
};
