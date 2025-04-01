// Copyright Choi JinWoo. All Rights Reserved.

#include "AdventureGameplayTag.h"

namespace AdventureGameplayTags
{
	/** Input Tag **/
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Look, "InputTag.Look");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Jump, "InputTag.Jump");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Move, "InputTag.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Sprint, "InputTag.Sprint");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Walk, "InputTag.Walk");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Wheel_Scroll, "InputTag.Wheel.Scroll");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_NormalAttack, "InputTag.NormalAttack");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_HeavyAttack, "InputTag.HeavyAttack");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Dodge, "InputTag.Dodge");

	
	/** Status Tag **/
	UE_DEFINE_GAMEPLAY_TAG(Status_Locomotion_Sprint, "Status.Locomotion.Sprint")
	UE_DEFINE_GAMEPLAY_TAG(Status_Locomotion_Falling, "Status.Locomotion.Falling")
	
	UE_DEFINE_GAMEPLAY_TAG(Status_CanHeavyAttack, "Status.CanHeavyAttack")
	UE_DEFINE_GAMEPLAY_TAG(Status_HeavyAttackActive, "Status.HeavyAttackActive")
	UE_DEFINE_GAMEPLAY_TAG(Status_Dodging, "Status.Dodging")

	
	/** Ability Tag **/
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_Attack_Normal, "Ability.Player.Attack.Normal")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_Attack_Heavy, "Ability.Player.Attack.Heavy")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_Dodge, "Ability.Player.Dodge")

	
	
	/** Damage Type Tag **/
	UE_DEFINE_GAMEPLAY_TAG(Damage, "Damage")
	UE_DEFINE_GAMEPLAY_TAG(Damage_Physical, "Damage.Physical")
	UE_DEFINE_GAMEPLAY_TAG(Damage_Fire, "Damage.Fire")
	UE_DEFINE_GAMEPLAY_TAG(Damage_Ice, "Damage.Ice")
	UE_DEFINE_GAMEPLAY_TAG(Damage_Darkness, "Damage.Darkness")
	UE_DEFINE_GAMEPLAY_TAG(Damage_Light, "Damage.Light")

	/** Event Tag **/
	UE_DEFINE_GAMEPLAY_TAG(Event_Hit_Melee, "Event.Hit.Melee")

	

}
