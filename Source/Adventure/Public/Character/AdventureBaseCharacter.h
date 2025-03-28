// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "AdventureBaseCharacter.generated.h"

class AAdventureWeaponBase;
class UDataAsset_StartUpDataBase;
class UAttributeSet;

UCLASS()
class ADVENTURE_API AAdventureBaseCharacter : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AAdventureBaseCharacter();

	/* Begin IAbilitySystemInterface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/* End IAbilitySystemInterface */

	UFUNCTION(BlueprintCallable)
	void RegisterSpawnedWeapon(AAdventureWeaponBase* InWeaponToRegister);
	
protected:
	/* Begin APawn Class */
	virtual void PossessedBy(AController* NewController) override;
	/* end APawn Class */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<AAdventureWeaponBase> OwningWeapon;


public:
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	

};
