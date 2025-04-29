// Copyright Choi JinWoo. All Rights Reserved.


#include "UI/WidgetController/InventoryWidgetController.h"

FItemInfoParams UInventoryWidgetController::GetItemInfoParams(const FGameplayTag& ItemTag) const
{
	check(ItemInfo);

	return ItemInfo->FindItemInfo(ItemTag);
	
}
