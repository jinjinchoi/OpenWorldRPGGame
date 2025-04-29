// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AdventureType/AdventureStructTypes.h"
#include "UObject/NoExportTypes.h"
#include "AdventureInventory.generated.h"

class UDataAsset_ItemInfo;

USTRUCT(BlueprintType)
struct FAllItem
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly)
	TArray<FItemSlot> Swords;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemSlot> Shields;
	
	UPROPERTY(BlueprintReadOnly)
	TArray<FItemSlot> Eatables;
	
};

/**
 * 
 */
UCLASS(Blueprintable)
class ADVENTURE_API UAdventureInventory : public UObject
{
	GENERATED_BODY()

public:
	void AddPickupsToAllItems(const FItemSlot& NewItem);
	

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataAsset_ItemInfo> PickupItemInfo;
	
	UPROPERTY(BlueprintReadOnly)
	FAllItem AllItems;
	
};
