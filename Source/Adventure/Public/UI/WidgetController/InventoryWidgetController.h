// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AdventureType/AdventureStructTypes.h"
#include "DataAsset/Item/DataAsset_ItemInfo.h"
#include "UI/WidgetController/AdventureWidgetControllerBase.h"
#include "InventoryWidgetController.generated.h"

DECLARE_DYNAMIC_MULTICAST_DELEGATE_TwoParams(FOnSlotButtonClicked, FItemSlot, ItemInSlot, int32, SlotIndex);
DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnItemToPickUpChanged, FItemInfoParams, OverlappedItemInfo);


class UDataAsset_ItemInfo;
/**
 * 
 */
UCLASS()
class ADVENTURE_API UInventoryWidgetController : public UAdventureWidgetControllerBase
{
	GENERATED_BODY()

public:
	virtual void BindCallbacksToDependencies() override;

	UFUNCTION(BlueprintCallable)
	void EquipItemToCharacter(const FItemSlot& SlotToEquip, const FGameplayTag& CharacterTag);
	
	UFUNCTION(BlueprintCallable)
	FItemInfoParams GetItemInfoParams(const FGameplayTag& ItemTag) const;

	UFUNCTION(BlueprintCallable)
	FString GetStatDisplayText(const FGameplayTag& ItemTag) const;

	UFUNCTION(BlueprintCallable)
	TArray<FItemSlot> GetSwordItemSlot() const;
	
	UFUNCTION(BlueprintCallable)
	TArray<FItemSlot> GetShieldItemSlot() const;

	UFUNCTION(BlueprintCallable)
	TArray<FItemSlot> GetEatableItemSlot() const;

	UFUNCTION(BlueprintCallable)
	void ApplyEatableItem(const FGameplayTag& ItemTag, const FGameplayTag& CharacterTagToApply);
	
	UFUNCTION(BlueprintCallable)
	void ConsumeEatableItem(const int32 SlotIndex);

	UPROPERTY(BlueprintAssignable, BlueprintCallable)
	FOnSlotButtonClicked SlotButtonClickedDelegate;

	UPROPERTY(BlueprintAssignable)
	FOnItemToPickUpChanged OnItemToPickUpChangedDelegate;

protected:
	UPROPERTY(EditDefaultsOnly)
	TObjectPtr<UDataAsset_ItemInfo> ItemInfo;


private:
	void UpdateSlotStatus(const FItemSlot& InSlotToEquip, const FGameplayTag& InCharacterTag) const;
};
