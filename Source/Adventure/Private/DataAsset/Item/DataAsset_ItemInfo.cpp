// Copyright Choi JinWoo. All Rights Reserved.


#include "DataAsset/Item/DataAsset_ItemInfo.h"

FItemInfoParams UDataAsset_ItemInfo::FindItemInfo(const FGameplayTag& ItemTag)
{
	for (const FItemInfoParams& ItemInfo : ItemInformation)
	{
		if (ItemInfo.ItemTag.MatchesTagExact(ItemTag))
		{
			return ItemInfo;
		}
	}

	return FItemInfoParams();
}
