// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/StartUpData/DataAsset_StartUpDataBase.h"
#include "DataAsset_StartUpData_Player.generated.h"

struct FPartyCharacterInfo;
/**
 * 
 */
UCLASS()
class ADVENTURE_API UDataAsset_StartUpData_Player : public UDataAsset_StartUpDataBase
{
	GENERATED_BODY()

public:
	void ApplySetByCallerEffectByCharacterInfo(UAdventureAbilitySystemComponent* InASC, const FPartyCharacterInfo& InCharacterInfo) const;

protected:
	UPROPERTY(EditDefaultsOnly, Category="Loaded")
	TSubclassOf<UGameplayEffect> SetByCallerGameplayEffect;
	
};
