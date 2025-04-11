// Copyright Choi JinWoo. All Rights Reserved.


#include "DataAsset/CharacterData/DataAsset_AbilityInfo.h"

FAbilityInfoForWidget UDataAsset_AbilityInfo::FindAbilityInfoByCharacterTag(const FGameplayTag& InCharacterTag)
{
	for (const FAbilityInfoForWidget& FoundAbilityInfo : CharacterAbilityInfo)
	{
		if (FoundAbilityInfo.CharacterTag.MatchesTagExact(InCharacterTag))
		{
			return FoundAbilityInfo;
		}
	}

	return FAbilityInfoForWidget();
}
