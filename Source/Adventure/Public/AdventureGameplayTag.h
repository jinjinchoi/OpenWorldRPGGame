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
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Walk);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Wheel_Scroll);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_NormalAttack);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_HeavyAttack);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Dodge);

	
	/** Status Tag **/
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Locomotion_Sprint);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Locomotion_Falling);
	
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_CanHeavyAttack);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_HeavyAttackActive);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Dodging);


	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_HitReact);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_HitReact_Front);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_HitReact_Back);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_HitReact_Left);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_HitReact_Right);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Dead);
	
	
	/** Ability Tag **/
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_Attack_Normal);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_Attack_Heavy);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_Dodge);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_HitPause);

	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Shared_HitReact);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Shared_Death);

	
	/** Damage Type Tag **/
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Physical);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Fire);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Ice);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Darkness);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Damage_Light);

	/** Event Tag **/
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_Hit_Melee);
	
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_HitReact);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_HitPause);

	

}
