// Copyright Choi JinWoo. All Rights Reserved.


#include "DataAsset/Input/DataAsset_InputConfig.h"

const UInputAction* UDataAsset_InputConfig::FindLocomotionInputActionByTag(const FGameplayTag& InputTag) const
{
	for (const FAdventureInputAction& InputActionConfig : LocomotionInputActions)
	{
		if (InputActionConfig.IsValid() && InputActionConfig.InputTag.MatchesTagExact(InputTag))
		{
			return InputActionConfig.InputAction;
		}
	}

	return nullptr;
	
}
