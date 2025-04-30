// Copyright Choi JinWoo. All Rights Reserved.


#include "Player/AdventureInventory.h"

#include "AdventureGameplayTag.h"
#include "DataAsset/Item/DataAsset_ItemInfo.h"

void UAdventureInventory::AddPickupsToAllItems(const FItemSlot& NewItem)
{
	check(PickupItemInfo);
	
	if (NewItem.ItemTag.MatchesTag(AdventureGameplayTags::Item_Eatable))
	{
		StackItemIntoInventory(NewItem);
		return;
	}
	
	if (NewItem.ItemTag.MatchesTag(AdventureGameplayTags::Item_Shield))
	{
		AllItems.Shields.Add(NewItem);
		return;
	}
	
	if (NewItem.ItemTag.MatchesTag(AdventureGameplayTags::Item_Sword))
	{
		AllItems.Swords.Add(NewItem);
	}
}

void UAdventureInventory::StackItemIntoInventory(const FItemSlot& NewItem)
{
	const int32 MaxStack = PickupItemInfo->FindItemInfo(NewItem.ItemTag).StackSize;
	int32 RemainingQuantity = NewItem.Quantity;
	
	// 기존 슬롯에 스택 채우기
	for (FItemSlot& EatableItem : AllItems.Eatables)
	{
		if (!EatableItem.ItemTag.MatchesTagExact(NewItem.ItemTag))
		{
			continue;
		}

		const int32 AvailableSpace = MaxStack - EatableItem.Quantity;
		if (AvailableSpace <= 0)
		{
			continue;
		}

		const int32 ToAdd = FMath::Min(RemainingQuantity, AvailableSpace);
		EatableItem.Quantity += ToAdd;
		RemainingQuantity -= ToAdd;

		if (RemainingQuantity <= 0)
		{
			return;
		}
	}

	// 남은 수량이 있다면 새 슬롯에 나눠서 추가
	while (RemainingQuantity > 0)
	{
		const int32 ToAdd = FMath::Min(RemainingQuantity, MaxStack);
		FItemSlot NewSlot;
		NewSlot.ItemTag = NewItem.ItemTag;
		NewSlot.Quantity = ToAdd;
		AllItems.Eatables.Add(NewSlot);
		RemainingQuantity -= ToAdd;
	}
}
