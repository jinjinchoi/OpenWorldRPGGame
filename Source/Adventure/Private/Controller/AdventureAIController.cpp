// Copyright Choi JinWoo. All Rights Reserved.


#include "Controller/AdventureAIController.h"

#include "DebugHelper.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Navigation/CrowdFollowingComponent.h"
#include "Perception/AIPerceptionComponent.h"
#include "Perception/AISenseConfig_Damage.h"
#include "Perception/AISenseConfig_Sight.h"

AAdventureAIController::AAdventureAIController(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UCrowdFollowingComponent>("PathFollowingComponent"))
{
	AISenseConfig_Sight = CreateDefaultSubobject<UAISenseConfig_Sight>("EnemySenseConfig_Sight");
	AISenseConfig_Sight->DetectionByAffiliation.bDetectEnemies = true;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectFriendlies = false;
	AISenseConfig_Sight->DetectionByAffiliation.bDetectNeutrals = false;
	AISenseConfig_Sight->SightRadius = 1500.f;
	AISenseConfig_Sight->LoseSightRadius = 2500.f;
	AISenseConfig_Sight->PeripheralVisionAngleDegrees = 60.f;
	
	AISenseConfig_Damage = CreateDefaultSubobject<UAISenseConfig_Damage>(TEXT("AISenseConfig_Damage"));

	EnemyPerceptionComponent = CreateDefaultSubobject<UAIPerceptionComponent>(TEXT("EnemyPerceptionComponent"));
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Sight);
	EnemyPerceptionComponent->ConfigureSense(*AISenseConfig_Damage);
	EnemyPerceptionComponent->SetDominantSense(UAISense_Sight::StaticClass());
	EnemyPerceptionComponent->OnTargetPerceptionUpdated.AddUniqueDynamic(this, &ThisClass::OnEnemyPerceptionUpdated);

	AAIController::SetGenericTeamId(FGenericTeamId(1));
}

ETeamAttitude::Type AAdventureAIController::GetTeamAttitudeTowards(const AActor& Other) const
{
	const APawn* PawnToCheck = Cast<const APawn>(&Other);
	const IGenericTeamAgentInterface* OtherTeamAgent = Cast<const IGenericTeamAgentInterface>(PawnToCheck->GetController());
	if (OtherTeamAgent && OtherTeamAgent->GetGenericTeamId() < GetGenericTeamId())
	{
		return ETeamAttitude::Hostile;
	}

	return ETeamAttitude::Friendly;
}

void AAdventureAIController::BeginPlay()
{
	Super::BeginPlay();
	
	if (UCrowdFollowingComponent* CrowdCom = Cast<UCrowdFollowingComponent>(GetPathFollowingComponent()))
	{
		CrowdCom->SetCrowdSimulationState(bEnableDetourCrowdAvoidance ? ECrowdSimulationState::Enabled : ECrowdSimulationState::Disabled);
		switch (DetourCrowdAvoidanceQuality)
		{
		case 1:
			CrowdCom->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Low);
			break;
		case 2:
			CrowdCom->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Medium);
			break;
		case 3:
			CrowdCom->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::Good);
			break;
		case 4:
			CrowdCom->SetCrowdAvoidanceQuality(ECrowdAvoidanceQuality::High);
		default:
			break;
		}

		CrowdCom->SetAvoidanceGroup(1);
		CrowdCom->SetGroupsToAvoid(1);
		CrowdCom->SetCrowdCollisionQueryRange(CollisionQueryRange);

	}
}

void AAdventureAIController::OnEnemyPerceptionUpdated(AActor* Actor, FAIStimulus Stimulus)
{
	if (UBlackboardComponent* BlackboardComponent = GetBlackboardComponent())
	{
		if (Stimulus.WasSuccessfullySensed() && Actor)
		{
			if (!BlackboardComponent->GetValueAsObject(FName("TargetActor")))
			{
				BlackboardComponent->SetValueAsObject(FName("TargetActor"), Actor);
			}
			LastSensedTime = GetWorld()->GetTimeSeconds();
		}
		else
		{
			const float CurrentTime = Actor->GetWorld()->GetTimeSeconds();
			float TimeSinceLastSensed = CurrentTime - LastSensedTime;

			if (TimeSinceLastSensed >= 10.f || !Actor)
			{
				BlackboardComponent->ClearValue(FName("TargetActor"));
			}
		}
	}
}
