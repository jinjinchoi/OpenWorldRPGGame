// Cypie

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "AdventurePlayerController.generated.h"

class UDamageTextComponent;
struct FGameplayTag;
/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventurePlayerController : public APlayerController
{
	GENERATED_BODY()

public:
	void ShowDamageNumber(const float DamageAmount, ACharacter* TargetCharacter, const bool bIsCriticalHit, const FGameplayTag& DamageType);

private:
	UPROPERTY(EditDefaultsOnly)
	TSubclassOf<UDamageTextComponent> DamageTextClass;
	
};
