// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "NativeGameplayTags.h"

namespace AdventureGameplayTags
{
	/** Input Tag **/
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Look);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Jump);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Move);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Sprint);

	/** Status Tag **/
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Locomotion_Sprint);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Locomotion_Falling);
}
