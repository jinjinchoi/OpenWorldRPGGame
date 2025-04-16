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
	/* End ICombat Interface */
	
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

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="MotionWarping")
	TObjectPtr<UMotionWarpingComponent> MotionWarpingComponent;
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpDataBase> CharacterStartUpData;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<AAdventureWeaponBase> OwningWeapon;

	bool bIsDead = false;
	bool bIsHitReacting = false;
	
	/**
	 * 태그 변경을 감지하는 것이 아닌 Ability 자체에서 인터페이스 함수를 호출하는 방식으로 사용하는 것이 통일성 유지에 좋을 것으로 보임.
	 * 추후 코드 리팩토링 작업을 수행한다면 이 부분을 고칠 필요가 있음.
	 */
	virtual void OnHitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);
	virtual void OnDeathReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount);


public:
	FORCEINLINE UAttributeSet* GetAttributeSet() const { return AttributeSet; }
	FORCEINLINE UMotionWarpingComponent* GetMotionWarpingComponent() const { return MotionWarpingComponent; }
	

};
