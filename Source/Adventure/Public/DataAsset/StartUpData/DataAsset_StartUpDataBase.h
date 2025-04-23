// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_StartUpDataBase.generated.h"

class UAdventureAbilitySystemComponent;
class UAdventureGameplayAbility;
class UGameplayEffect;

USTRUCT(BlueprintType)
struct FAdventureAbilityInfo
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, meta = (Categories = "InputTag"))
	FGameplayTag InputTag = FGameplayTag();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSubclassOf<UAdventureGameplayAbility> AbilityToGrant;
	
};

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

	UPROPERTY(EditDefaultsOnly, Category="StartUpData", meta = (TitleProperty = "InputTag"))
	TArray<FAdventureAbilityInfo> StartUpAbilityInfo;

	/* 제일 처음 적용할 게임플레이 이펙트 */
	UPROPERTY(EditDefaultsOnly, Category="StartUpData")
	TArray<TSubclassOf<UGameplayEffect>> StartUpGameplayEffects;


private:
	void GrantAbilities(const TArray<TSubclassOf<UAdventureGameplayAbility>>& InAbilityToGive, UAdventureAbilitySystemComponent* InASC, int32 ApplyLevel = 1);
	void GrantGameplayEffect(const TArray<TSubclassOf<UGameplayEffect>>& InGameplayEffectsToGive, UAdventureAbilitySystemComponent* InASC, int32 ApplyLevel = 1);
};
