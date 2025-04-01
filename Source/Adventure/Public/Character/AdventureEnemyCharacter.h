// Cypie

#pragma once

#include "CoreMinimal.h"
#include "Character/AdventureBaseCharacter.h"
#include "AdventureEnemyCharacter.generated.h"

/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventureEnemyCharacter : public AAdventureBaseCharacter
{
	GENERATED_BODY()

public:
	AAdventureEnemyCharacter();

protected:
	virtual void PossessedBy(AController* NewController) override;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Movement")
	float MaxWalkSpeed = 400;

private:
	void InitEnemyStartUpData() const;
	
};
