// Copyright Choi JinWoo. All Rights Reserved.

#include "AdventureGameplayTag.h"

namespace AdventureGameplayTags
{
	/** Input Tag **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Sprint, "InputTag.Sprint");

	/** Status Tag **/
	UE_DEFINE_GAMEPLAY_TAG(Status_Locomotion_Sprint, "Status.Locomotion.Sprint")
	UE_DEFINE_GAMEPLAY_TAG(Status_Locomotion_Falling, "Status.Locomotion.Falling")
	
	
}
