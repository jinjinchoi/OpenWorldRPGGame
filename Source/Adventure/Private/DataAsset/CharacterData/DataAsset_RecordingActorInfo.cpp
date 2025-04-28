// Copyright Choi JinWoo. All Rights Reserved.


#include "DataAsset/CharacterData/DataAsset_RecordingActorInfo.h"

FRecordingInfo UDataAsset_RecordingActorInfo::GetRecordingInfoByCharacterTag(const FGameplayTag& CharacterTag)
{
	for (const FRecordingInfo& RecordingInfo : RecordingInfos)
	{
		if (RecordingInfo.CharacterTag.MatchesTagExact(CharacterTag))
		{
			return RecordingInfo;
		}
	}

	return FRecordingInfo();
}
