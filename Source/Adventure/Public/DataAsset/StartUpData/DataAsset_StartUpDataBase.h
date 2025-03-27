// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UAdventureAbilitySystemComponent;
class UAdventureGameplayAbility;
/**
 * 
 */
UCLASS()
class ADVENTURE_API UDataAsset_StartUpDataBase : public UDataAsset
{
	GENERATED_BODY()

public:
	virtual void GiveToAbilitySystemComponent(UAdventureAbilitySystemComponent* InASC, int32 ApplyLevel = 1);
	
	
protected:
	/* Ability가 주어지면(Given) 실행할 Ability */
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UAdventureGameplayAbility>> ActivateOnGivenAbilities;

	/* 특정 조건에 따라 반응하여 실행할 어빌리티 ex) Death, HitReact */
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UAdventureGameplayAbility>> ReactiveAbilities;

private:
	void GrantAbilities(const TArray<TSubclassOf<UAdventureGameplayAbility>>& InAbilityToGive, UAdventureAbilitySystemComponent* InASC, int32 ApplyLevel = 1);
	
};
