// Copyright Choi JinWoo. All Rights Reserved.


#include "Player/AdventureInventory.h"

#include "AdventureGameplayTag.h"
#include "DataAsset/Item/DataAsset_ItemInfo.h"

void UAdventureInventory::AddPickupsToAllItems(const FItemSlot& NewItem)
{
	if (NewItem.ItemTag.MatchesTag(AdventureGameplayTags::Item_Eatable))
	{
		for (FItemSlot& EatableItem : AllItems.Eatables)
		{
			// 인벤토리에 있는 아이템이랑 새로운 아이템 태그 확인
			if (!EatableItem.ItemTag.MatchesTagExact(NewItem.ItemTag))
			{
				continue;
			}

			// 스택 확인해서 스택 채우기
			if (PickupItemInfo->FindItemInfo(NewItem.ItemTag).StackSize > EatableItem.Quantity)
			{
				EatableItem.Quantity += EatableItem.Quantity + NewItem.Quantity;
				return;
			}
		}
		AllItems.Eatables.Add(NewItem);
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
