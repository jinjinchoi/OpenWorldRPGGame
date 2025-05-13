// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "AbilitySystemInterface.h"
#include "GameplayTagContainer.h"
#include "Interface/CombatInterface.h"
#include "AdventureBaseCharacter.generated.h"

class AAdventureWeaponBase;
class UDataAsset_StartUpDataBase;
class UAttributeSet;
class UMotionWarpingComponent;

UCLASS()
class ADVENTURE_API AAdventureBaseCharacter : public ACharacter, public IAbilitySystemInterface, public ICombatInterface
{
	GENERATED_BODY()

public:
	AAdventureBaseCharacter(const FObjectInitializer& ObjectInitializer);

	/* Begin IAbilitySystemInterface */
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	/* End IAbilitySystemInterface */

	/* Begin ICombat Interface */
	virtual void ToggleWeaponCollision_Implementation(const bool bIsEnable, const EAdventureWeaponType AdventureWeaponType = EAdventureWeaponType::Weapon) override;
	virtual bool IsDead_Implementation() const override;
	virtual void OnCharacterDied_Implementation() override;
	virtual int32 GetCharacterLevel() const override;
	/* End ICombat Interface */
	
	UFUNCTION(BlueprintCallable)
	void RegisterSpawnedWeapon(AAdventureWeaponBase* InWeaponToRegister);


	
protected:
	/* Begin APawn Class */
	virtual void PossessedBy(AController* NewController) override;
	virtual void Destroyed() override;
	/* end APawn Class */
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAbilitySystemComponent> AbilitySystemComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="AbilitySystem")
	TObjectPtr<UAttributeSet> AttributeSet;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MotionWarping")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<AAdventureWeaponBase> OwningWeapon;

	bool bIsDead = false;
	bool bIsHitReacting = false;
	
	virtual void OnHitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);

public:
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	FORCEINLINE UMotionWarpingComponent* GetMotionWarpingComponent() const { return MotionWarpingComponent; }
	

};
