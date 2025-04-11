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
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Climb_Stop, "InputTag.Climb.Stop");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Climb_Move, "InputTag.Climb.Move");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Climb_Hop, "InputTag.Climb.Hop");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_NormalAbility, "InputTag.NormalAbility");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_SpecialAbility, "InputTag.SpecialAbility");

	
	/** Status Tag **/
	UE_DEFINE_GAMEPLAY_TAG(Status_Locomotion_Sprint, "Status.Locomotion.Sprint")
	UE_DEFINE_GAMEPLAY_TAG(Status_Locomotion_Falling, "Status.Locomotion.Falling")
	UE_DEFINE_GAMEPLAY_TAG(Status_Locomotion_Climbing, "Status.Locomotion.Climbing")
	
	UE_DEFINE_GAMEPLAY_TAG(Status_CanHeavyAttack, "Status.CanHeavyAttack")
	UE_DEFINE_GAMEPLAY_TAG(Status_HeavyAttackActive, "Status.HeavyAttackActive")
	UE_DEFINE_GAMEPLAY_TAG(Status_Dodging, "Status.Dodging")
	
	UE_DEFINE_GAMEPLAY_TAG(Status_HitReact, "Status.HitReact")
	UE_DEFINE_GAMEPLAY_TAG(Status_HitReact_Front, "Status.HitReact.Front")
	UE_DEFINE_GAMEPLAY_TAG(Status_HitReact_Back, "Status.HitReact.Back")
	UE_DEFINE_GAMEPLAY_TAG(Status_HitReact_Left, "Status.HitReact.Left")
	UE_DEFINE_GAMEPLAY_TAG(Status_HitReact_Right, "Status.HitReact.Right")
	UE_DEFINE_GAMEPLAY_TAG(Status_Dead, "Status.Dead")

	
	/** Ability Tag **/
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_Attack_Normal, "Ability.Player.Attack.Normal")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_Attack_Heavy, "Ability.Player.Attack.Heavy")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_Dodge, "Ability.Player.Dodge")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_HitPause, "Ability.Player.HitPause")
	
	UE_DEFINE_GAMEPLAY_TAG(Ability_Shared_HitReact, "Ability.Shared.HitReact")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Shared_Death, "Ability.Shared.Death")
	
	
	/** Damage Type Tag **/
	UE_DEFINE_GAMEPLAY_TAG(Damage, "Damage")
	UE_DEFINE_GAMEPLAY_TAG(Damage_Physical, "Damage.Physical")
	UE_DEFINE_GAMEPLAY_TAG(Damage_Fire, "Damage.Fire")
	UE_DEFINE_GAMEPLAY_TAG(Damage_Ice, "Damage.Ice")
	UE_DEFINE_GAMEPLAY_TAG(Damage_Darkness, "Damage.Darkness")
	UE_DEFINE_GAMEPLAY_TAG(Damage_Light, "Damage.Light")

	/** Event Tag **/
	UE_DEFINE_GAMEPLAY_TAG(Event_Hit_Melee, "Event.Hit.Melee")
	
	UE_DEFINE_GAMEPLAY_TAG(Event_HitReact, "Event.HitReact")
	UE_DEFINE_GAMEPLAY_TAG(Event_HitPause, "Event.HitPause")

	/** Class Tag **/
	UE_DEFINE_GAMEPLAY_TAG(CharacterClass_Player_Warrior, "CharacterClass.Player.Warrior")
	
	

}
