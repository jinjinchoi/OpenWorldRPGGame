// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/AdventureBaseCharacter.h"
#include "Interface/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AdventureEnemyCharacter.generated.h"

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
	virtual void OnEnemyDied_Implementation() override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MaxWalkSpeed = 400;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Vital")
	TObjectPtr<UWidgetComponent> EnemyHealthBar;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeDelegate OnHealthChangeDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnAttributeChangeDelegate OnMaxHealthChangeDelegate;

	void BindGameplayTagChange();

	/* Begin AAdventureBaseCharacter */
	virtual void OnHitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;
	virtual void OnDeathReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount) override;
	/* End AAdventureBaseCharacter */

	/* AI */

	UPROPERTY()
	TObjectPtr<AAdventureAIController> AdventureAIController;

	UPROPERTY(EditAnywhere, Category="AI")
	TObjectPtr<UBehaviorTree> BehaviorTree;
	


private:
	void InitEnemyStartUpData() const;

	
	
};
