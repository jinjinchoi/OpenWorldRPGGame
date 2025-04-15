// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AdventureGameplayAbility.h"
#include "AdventureTargetLockAbility.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureTargetLockAbility : public UAdventureGameplayAbility
{
	GENERATED_BODY()

protected:
	/* Begin UGameplayAbility Interface */
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	/* End UGameplayAbility Interface */
	
	UFUNCTION(BlueprintCallable)
	void OnTargetLockTick(float DeltaTime);

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	bool bDrawDebugShape = false;

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	TSubclassOf<UUserWidget> TargetLockWidgetClass;

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	float TargetLockRotationInterpSpeed = 5.f;

	UPROPERTY(EditDefaultsOnly, Category="Target Lock")
	float TargetLockCameraOffsetDistance = 20.f;	

private:
	
	void TryLockOnTarget();
	void FindClosestActorToMouse();
	void DrawTargetLockWidget();
	void CancelTargetLockAbility();
	void CleanUp();
	void SetTargetLockWidgetPosition();

	
	UPROPERTY()
	TArray<AActor*> TargetActors;
	
	UPROPERTY()
	TObjectPtr<AActor> ClosestActorToMouse;

	UPROPERTY()
	TObjectPtr<UUserWidget> TargetLockWidget;
	
};
