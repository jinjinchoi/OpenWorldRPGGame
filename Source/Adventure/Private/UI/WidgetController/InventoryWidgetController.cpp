// Copyright Choi JinWoo. All Rights Reserved.


#include "UI/WidgetController/InventoryWidgetController.h"

#include "Character/AdventurePlayerCharacter.h"
#include "Item/Pickups/AdventureInventoryItem.h"
#include "Player/AdventureInventory.h"
#include "Player/AdventurePlayerState.h"

void UInventoryWidgetController::BindCallbacksToDependencies()
{
	check(PlayerController);
	
	if (AAdventurePlayerCharacter* PlayerCharacter = Cast<AAdventurePlayerCharacter>(PlayerController->GetPawn()))
	{
		PlayerCharacter->OnOverlappedItemChangedDelegate.Unbind();
		
		PlayerCharacter->OnOverlappedItemChangedDelegate.BindWeakLambda(
			PlayerCharacter, [this](const TArray<TWeakObjectPtr<AAdventureInventoryItem>>& OverlappedItems)
			{
				if (OverlappedItems.IsEmpty())
				{
					OnItemToPickUpChangedDelegate.Broadcast(FItemInfoParams());
					return;
				}

				OnItemToPickUpChangedDelegate.Broadcast(FItemInfoParams());
				
				for (const TWeakObjectPtr<AAdventureInventoryItem>& WeakItem : OverlappedItems)
				{
					if (!WeakItem.IsValid()) continue;

					const FItemInfoParams FoundInfo = ItemInfo->FindItemInfo(WeakItem->ItemTag);
					OnItemToPickUpChangedDelegate.Broadcast(FoundInfo);
				}
			}
		);
	}
}

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
