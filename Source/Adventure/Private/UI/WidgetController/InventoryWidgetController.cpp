// Copyright Choi JinWoo. All Rights Reserved.


#include "UI/WidgetController/InventoryWidgetController.h"

#include "AdventureGameplayTag.h"
#include "Character/AdventurePlayerCharacter.h"
#include "GameManager/ControllableCharacterManager.h"
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

void UInventoryWidgetController::EquipItemToCharacter(const FItemSlot& SlotToEquip, const FGameplayTag& CharacterTag)
{
	check(PlayerController);
	
	if (AAdventurePlayerCharacter* PlayerCharacter = Cast<AAdventurePlayerCharacter>(PlayerController->GetPawn()))
	{
		if (PlayerCharacter->GetCharacterClassTag() == CharacterTag)
		{
			PlayerCharacter->ApplyEquipmentEffect(SlotToEquip.ItemTag);
			PlayerCharacter->AddCharacterInfoToManager();
		}
		else
		{
			AAdventurePlayerState* AdventurePlayerState = CastChecked<AAdventurePlayerState>(PlayerState);

			FPartyCharacterInfo* CharacterInfo = AdventurePlayerState->GetControllableCharacterManager()->FindCharacterInfoInOwningCharacters(CharacterTag);
			check(CharacterInfo);

			if (SlotToEquip.ItemTag.MatchesTag(AdventureGameplayTags::Item_Sword))
			{
				CharacterInfo->WeaponTag = SlotToEquip.ItemTag;
			}
			else if (SlotToEquip.ItemTag.MatchesTag(AdventureGameplayTags::Item_Shield))
			{
				CharacterInfo->ShieldTag = SlotToEquip.ItemTag;
			}
			
		}

		UpdateSlotStatus(SlotToEquip, CharacterTag);
	}
	
}

void UInventoryWidgetController::UpdateSlotStatus(const FItemSlot& InSlotToEquip, const FGameplayTag& InCharacterTag) const
{
	if (AAdventurePlayerState* AdventurePlayerState = Cast<AAdventurePlayerState>(PlayerState))
	{
		UAdventureInventory* Inventory = AdventurePlayerState->GetPickupItemInventory();
		check(Inventory);

		if (InSlotToEquip.ItemTag.MatchesTag(AdventureGameplayTags::Item_Sword))
		{
			for (FItemSlot& Sword : Inventory->AllItems.Swords)
			{
				if (Sword.SlotID == InSlotToEquip.SlotID)
				{
					Sword.EquippedCharacterTag = InCharacterTag;
					return;
				}
			}
		}

		if (InSlotToEquip.ItemTag.MatchesTag(AdventureGameplayTags::Item_Shield))
		{
			for (FItemSlot& Shield : Inventory->AllItems.Shields)
			{
				if (Shield.SlotID == InSlotToEquip.SlotID)
				{
					Shield.EquippedCharacterTag = InCharacterTag;
					return;
				}
			}
		}

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

