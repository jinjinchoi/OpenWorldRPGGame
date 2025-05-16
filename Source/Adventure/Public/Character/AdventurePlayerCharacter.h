// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "ActiveGameplayEffectHandle.h"
#include "GameplayTagContainer.h"
#include "AdventureType/AdventureStructTypes.h"
#include "Character/AdventureBaseCharacter.h"
#include "Interface/PlayerInterface.h"
#include "AdventurePlayerCharacter.generated.h"

class UDataAsset_StartUpData_Player;
class UDataAsset_ItemInfo;
class AAdventureInventoryItem;
DECLARE_DELEGATE_OneParam(FOnMovementModechanged, const ECharacterMovementType /* Movement Type */);
DECLARE_DELEGATE_OneParam(FOnOverlappedItemChanged, TArray<TWeakObjectPtr<AAdventureInventoryItem>> /* Overlap Item Array */);
DECLARE_DELEGATE(FOnCharacterLevelUp);

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
	
	/* Begin Player Interface */
	virtual void ShowWeaponMesh_Implementation() override;
	virtual void HideWeaponMesh_Implementation() override;
	virtual void OnStaminaDepleted() override;
	virtual void PickUpItemBeginOverlap(AAdventureInventoryItem* InOverlappedItem) override;
	virtual void PickUpItemEndOverlap(AAdventureInventoryItem* InOverlappedItem) override;
	virtual void ForceCharacterChange(const int32 IndexToChange) override;
	virtual void ChangeCharacterPartyIndex(const int32 IndexToChange) override;
	virtual FGameplayTag GetOwningCharacterTag() override;
	virtual void AddMoney(const int32 MoneyToAdd) override;
	virtual void LevelUp(const int32 LevelUpAmount = 1) override;
	/* End Player Interface */

	/* Begin Combat Interface */
	virtual void OnCharacterDied_Implementation() override;
	/* End Combat Interface */

	void ApplyEquipmentEffect(const FGameplayTag& EquipmentTag);
	void RemoveEquipmentEffect(const bool bIsSwordEffect) const;
	void AddCharacterInfoToManager() const;
	void ApplyRecoveryEffect(const float RecoveryAmount) const;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Character Data")
	int32 CurrentCharacterIndex = 1;
	
	FGameplayTag EquippedSwordTag;
	FGameplayTag EquippedShieldTag;
	
	FOnMovementModechanged OnMovementModeChangedDelegate;
	FOnOverlappedItemChanged OnOverlappedItemChangedDelegate;
	FOnCharacterLevelUp OnCharacterLevelUpDelegate;

protected:
	virtual void BeginPlay() override;
	virtual void PossessedBy(AController* NewController) override;
	void InitPlayerStartUpData() const;
	void BindGameplayTagChanged();

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
	
	UPROPERTY(EditDefaultsOnly, Category="Gameplay Effect")
	TSubclassOf<UGameplayEffect> RecoveryEffect;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay Effect")
	TSubclassOf<UGameplayEffect> SwordGameplayEffect;
	FActiveGameplayEffectHandle SwordActiveGameplayEffectHandle;

	UPROPERTY(EditDefaultsOnly, Category="Gameplay Effect")
	TSubclassOf<UGameplayEffect> ShieldGameplayEffect;
	FActiveGameplayEffectHandle ShieldActiveGameplayEffectHandle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TObjectPtr<UDataAsset_StartUpData_Player> CharacterStartUpData;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData", meta=(Categories ="CharacterClass.Player"))
	FGameplayTag CharacterTag;
	
	UFUNCTION(BlueprintImplementableEvent)
	void SetWeaponMeshVisibility(bool bIsVisible);
	
	UPROPERTY(EditDefaultsOnly, Category="Equipment")
	TObjectPtr<UDataAsset_ItemInfo> EquipmentDataAsset;

private:
	bool ApplyStaminaCostEffect(const TSubclassOf<UGameplayEffect>& InEffect);
	void RemoveStaminaCostEffect();
	void InitPlayerCharacterData();

	FActiveGameplayEffectHandle StaminaCostEffectHandle;
	TArray<TWeakObjectPtr<AAdventureInventoryItem>> OverlappedItems;
	

public:
	FORCEINLINE UAdventureMovementComponent* GetAdventureMovementComponent() const { return AdventureMovementComponent; }
	FORCEINLINE FGameplayTag GetCharacterClassTag() const { return CharacterTag; }
	FORCEINLINE bool IsSprinting() const { return bIsSprint; }
	void StartSprint();

protected:

		
#pragma region Components
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Movement")
	TObjectPtr<UAdventureMovementComponent> AdventureMovementComponent;
	
#pragma endregion

#pragma region Input
	
	virtual void Input_Jump() override;
	virtual void Input_Look(const FInputActionValue& InputActionValue) override;
	
	virtual void Input_Move(const FInputActionValue& InputActionValue) override;
	virtual void Input_StopMove() override;
	virtual void Input_Sprint_Started() override;
	virtual void Input_Sprint_Completed() override;
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

	/* Interaction */
	virtual void Input_Interaction() override;

	
#pragma endregion
	
};
