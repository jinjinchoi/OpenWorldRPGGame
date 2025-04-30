// Copyright Choi JinWoo. All Rights Reserved.


#include "UI/WidgetController/InventoryWidgetController.h"

#include "Player/AdventureInventory.h"
#include "Player/AdventurePlayerState.h"

FItemInfoParams UInventoryWidgetController::GetItemInfoParams(const FGameplayTag& ItemTag) const
{
	check(ItemInfo);

	return ItemInfo->FindItemInfo(ItemTag);
	
}

TArray<FItemSlot> UInventoryWidgetController::GetSwordItemSlot() const
{
	if (AAdventurePlayerState* AdventurePlayerState = Cast<AAdventurePlayerState>(PlayerState))
	{
		UAdventureInventory* Inventory = AdventurePlayerState->GetPickupItemInventory();
		check(Inventory);

		return Inventory->AllItems.Swords;
	}

	return TArray<FItemSlot>();
}

TArray<FItemSlot> UInventoryWidgetController::GetShieldItemSlot() const
{
	if (AAdventurePlayerState* AdventurePlayerState = Cast<AAdventurePlayerState>(PlayerState))
	{
		UAdventureInventory* Inventory = AdventurePlayerState->GetPickupItemInventory();
		check(Inventory);

		return Inventory->AllItems.Shields;
	}

	return TArray<FItemSlot>();
}

TArray<FItemSlot> UInventoryWidgetController::GetEatableItemSlot() const
{
	if (AAdventurePlayerState* AdventurePlayerState = Cast<AAdventurePlayerState>(PlayerState))
	{
		UAdventureInventory* Inventory = AdventurePlayerState->GetPickupItemInventory();
		check(Inventory);

		return Inventory->AllItems.Eatables;
	}

	return TArray<FItemSlot>();
}
