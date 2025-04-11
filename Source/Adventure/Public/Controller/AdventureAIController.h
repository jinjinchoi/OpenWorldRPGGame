// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "AdventureAIController.generated.h"

class UAISenseConfig_Damage;
class UAISenseConfig_Sight;
/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventureAIController : public AAIController
{
	GENERATED_BODY()

public:
	AAdventureAIController(const FObjectInitializer& ObjectInitializer);

	/* Begin IGenericTeamAgentInterface Interface.*/
	virtual ETeamAttitude::Type GetTeamAttitudeTowards(const AActor& Other) const override;
	/* End IGenericTeamAgentInterface Interface. */

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAIPerceptionComponent> EnemyPerceptionComponent;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAISenseConfig_Sight> AISenseConfig_Sight;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly)
	TObjectPtr<UAISenseConfig_Damage> AISenseConfig_Damage;

	UFUNCTION()
	virtual void OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus);

private:
	UPROPERTY(EditDefaultsOnly, Category="Detour Crowd Avoid Config")
	bool bEnableDetourCrowdAvoidance = true;

	UPROPERTY(EditDefaultsOnly, Category="Detour Crowd Avoid Config", meta = (EditCondition = "bEnableDetourCrowdAvoidance", UIMin = "1", UIMax = "4"))
	int32 DetourCrowdAvoidanceQuality = 4;

	UPROPERTY(EditDefaultsOnly, Category="Detour Crowd Avoid Config", meta = (EditCondition = "bEnableDetourCrowdAvoidance"))
	float CollisionQueryRange = 600.f;

	float LastSensedTime = 0.f;
	
};
