// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/AdventureBaseCharacter.h"
#include "Interface/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AdventureEnemyCharacter.generated.h"

class UDataAsset_StartUpData_Enemy;
class UBoxComponent;
class AAdventureAIController;
class UWidgetComponent;
class UBehaviorTree;
/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventureEnemyCharacter : public AAdventureBaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAdventureEnemyCharacter(const FObjectInitializer& ObjectInitializer);
	virtual void OnCharacterDied_Implementation() override;

protected:
	/* Begin APawn */
	virtual void PossessedBy(AController* NewController) override;
	virtual void BeginPlay() override;
	/* End APawn */

#if WITH_EDITOR
	/* Begin UObject */
	virtual void PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent) override;
	/* End UObject */
#endif
	
	/* Begin AAdventureBaseCharacter */
	virtual void OnHitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;
	/* End AAdventureBaseCharacter */

	/* Begin ICombatInterface */
	virtual void ToggleWeaponCollision_Implementation(const bool bIsEnable, const EAdventureWeaponType AdventureWeaponType = EAdventureWeaponType::Weapon) override;
	/* End ICombatInterface */
	
	void BindGameplayTagChanged();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "CharacterData")
	TSoftObjectPtr<UDataAsset_StartUpData_Enemy> CharacterStartUpData;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "CharacterData")
	int32 EnemyLevel = 1;

	UFUNCTION()
	virtual void OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<UBoxComponent> LeftHandCollisionBox;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Combat")
	TObjectPtr<UBoxComponent> RightHandCollisionBox;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat")
	FName LeftHandCollisionBoxAttachBoneName;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category="Combat")
	FName RightHandCollisionBoxAttachBoneName;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MaxWalkSpeed = 400;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Vital")
	TObjectPtr<UWidgetComponent> EnemyHealthBar;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeDelegate OnHealthChangeDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeDelegate OnMaxHealthChangeDelegate;

	/* AI */
	UPROPERTY()
	TObjectPtr<AAdventureAIController> AdventureAIController;

	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;

private:
	void InitEnemyStartUpData() const;

	UPROPERTY()
	TArray<AActor*> OverlappedActors;

	
	
};
