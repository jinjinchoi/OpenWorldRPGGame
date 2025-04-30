// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AdventureType/AdventureStructTypes.h"
#include "DataAsset/Item/DataAsset_ItemInfo.h"
#include "UI/WidgetController/AdventureWidgetControllerBase.h"
#include "InventoryWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlotButtonClicked, FItemSlot, ItemInSlot, int32, SlotIndex);

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

	UFUNCTION(BlueprintCallable)
	TArray<FItemSlot> GetSwordItemSlot() const;
	
	UFUNCTION(BlueprintCallable)
	TArray<FItemSlot> GetShieldItemSlot() const;

	UFUNCTION(BlueprintCallable)
	TArray<FItemSlot> GetEatableItemSlot() const;

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSlotButtonClicked SlotButtonClickedDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataAsset_ItemInfo> ItemInfo;
	
};
