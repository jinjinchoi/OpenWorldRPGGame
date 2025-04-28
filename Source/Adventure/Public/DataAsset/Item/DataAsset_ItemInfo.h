// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameplayTagContainer.h"
#include "Engine/DataAsset.h"
#include "DataAsset_ItemInfo.generated.h"


USTRUCT(BlueprintType)
struct FItemInfoParams
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FGameplayTag ItemTag; 

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FName ItemName = FName();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	FText Description = FText();

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TSoftObjectPtr<UTexture2D> Thumbnail = nullptr;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	int32 StackSize = 1;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float AttackPower = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float DefensePower = 0.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	float RecoveryAmount = 0.f;
	
};

/**
 * 
 */
UCLASS()
class ADVENTURE_API UDataAsset_ItemInfo : public UDataAsset
{
	GENERATED_BODY()

public:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly)
	TArray<FItemInfoParams> ItemInformation;

	FItemInfoParams FindItemInfo(const FGameplayTag& ItemTag);
	
};
