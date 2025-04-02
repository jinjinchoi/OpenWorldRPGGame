// Cypie

#pragma once

#include "CoreMinimal.h"
#include "Character/AdventureBaseCharacter.h"
#include "Interface/EnemyInterface.h"
#include "AdventureEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventureEnemyCharacter : public AAdventureBaseCharacter, public IEnemyInterface
{
	GENERATED_BODY()

public:
	AAdventureEnemyCharacter();
	virtual void OnEnemyDied_Implementation() override;

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MaxWalkSpeed = 400;

private:
	void InitEnemyStartUpData() const;
	
};
