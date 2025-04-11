// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "Character/AdventureBaseCharacter.h"
#include "Interface/EnemyInterface.h"
#include "UI/WidgetController/OverlayWidgetController.h"
#include "AdventureEnemyCharacter.generated.h"

class UWidgetComponent;
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

private:
	void InitEnemyStartUpData() const;
	
};
