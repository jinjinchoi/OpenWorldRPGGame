// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystem/Abilities/AdventureGameplayAbility.h"
#include "GameManager/ControllableCharacterManager.h"
#include "AdventureChangeCharacterAbility.generated.h"

class AAdventurePlayerCharacter;
class UControllableCharacterManager;
/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureChangeCharacterAbility : public UAdventureGameplayAbility
{
	GENERATED_BODY()

public:
	/* Begin UGameplayAbility Interface */
	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;
	/* End UGameplayAbility Interface */

protected:
	/* 로드시 사용할 게임플레이 이펙트 */
	UPROPERTY(EditDefaultsOnly, Category="LoadData")
	TSubclassOf<UGameplayEffect> CharacterLoadGameplayEffect;
	
	UFUNCTION(BlueprintCallable, Category="Character Management")
	void OnCharacterChangeAbilityActivated();
	
	UFUNCTION(BlueprintCallable, Category="Character Management")
	void SpawnNewCharacterAndRemoveOldCharacter(const int32 InCharacterIndex);

	UPROPERTY(BlueprintReadOnly)
	TObjectPtr<UControllableCharacterManager> CharacterManager;

private:
	void CancelCharacterChangeAbility();
	AAdventurePlayerCharacter* GetAdventurePlayerCharacter() const;
	
	FPartyCharacterInfo CachedPartyInfo;
	int32 CachedCharacterIndex;
	
};
