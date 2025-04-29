// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "DataAsset/Item/DataAsset_ItemInfo.h"
#include "UI/WidgetController/AdventureWidgetControllerBase.h"
#include "InventoryWidgetController.generated.h"

class UDataAsset_ItemInfo;
/**
 * 
 */
UCLASS()
class ADVENTURE_API UInventoryWidgetController : public UAdventureWidgetControllerBase
{
	GENERATED_BODY()

public:
	UFUNCTION(BlueprintCallable)
	FItemInfoParams GetItemInfoParams(const FGameplayTag& ItemTag) const;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataAsset_ItemInfo> ItemInfo;
	
};
