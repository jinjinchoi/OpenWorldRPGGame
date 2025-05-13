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
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ESkill, "InputTag.ESkill");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_RSkill, "InputTag.RSkill");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ChangeCharacter_One, "InputTag.ChangeCharacter.One");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ChangeCharacter_Two, "InputTag.ChangeCharacter.Two");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_ChangeCharacter_Three, "InputTag.ChangeCharacter.Three");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Interaction, "InputTag.Interaction");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_OpenMenu, "InputTag.OpenMenu");
	
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable, "InputTag.Toggleable");
	UE_DEFINE_GAMEPLAY_TAG(InputTag_Toggleable_TargetLock, "InputTag.Toggleable.TargetLock");

	
	/** Status Tag **/
	UE_DEFINE_GAMEPLAY_TAG(Status_Locomotion_Sprint, "Status.Locomotion.Sprint")
	UE_DEFINE_GAMEPLAY_TAG(Status_Locomotion_Falling, "Status.Locomotion.Falling")
	UE_DEFINE_GAMEPLAY_TAG(Status_Locomotion_Climbing, "Status.Locomotion.Climbing")
	
	UE_DEFINE_GAMEPLAY_TAG(Status_CanHeavyAttack, "Status.CanHeavyAttack")
	UE_DEFINE_GAMEPLAY_TAG(Status_HeavyAttackActive, "Status.HeavyAttackActive")
	
	UE_DEFINE_GAMEPLAY_TAG(Status_HitReact, "Status.HitReact")
	UE_DEFINE_GAMEPLAY_TAG(Status_Dead, "Status.Dead")
	
	UE_DEFINE_GAMEPLAY_TAG(Status_Player_Dodging, "Status.Player.Dodging")
	UE_DEFINE_GAMEPLAY_TAG(Status_Player_CanCounterAttack, "Status.Player.CanCounterAttack")
	UE_DEFINE_GAMEPLAY_TAG(Status_Player_TargetLock, "Status.Player.TargetLock")
	UE_DEFINE_GAMEPLAY_TAG(Status_Player_CombatAbilityActivated, "Status.Player.CombatAbilityActivated")
	
	UE_DEFINE_GAMEPLAY_TAG(Status_Enemy_Strafing, "Status.Enemy.Strafing")
	
	UE_DEFINE_GAMEPLAY_TAG(Status_Shared_Invincible, "Status.Shared.Invincible")
	UE_DEFINE_GAMEPLAY_TAG(Status_Shared_SuperArmor, "Status.Shared.SuperArmor")

	
	/** Ability Tag **/
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_Attack_Normal, "Ability.Player.Attack.Normal")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_Attack_Heavy, "Ability.Player.Attack.Heavy")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_Dodge, "Ability.Player.Dodge")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_HitPause, "Ability.Player.HitPause")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_PerfectDodge, "Ability.Player.PerfectDodge")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_TargetLock, "Ability.Player.TargetLock")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_ESkill, "Ability.Player.ESkill")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_RSkill, "Ability.Player.RSkill")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Player_CharacterChange, "Ability.Player.CharacterChange")
	
	UE_DEFINE_GAMEPLAY_TAG(Ability_Enemy_Attack_Melee, "Ability.Enemy.Attack.Melee")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Enemy_Attack_Ranged, "Ability.Enemy.Attack.Ranged")
	
	UE_DEFINE_GAMEPLAY_TAG(Ability_Shared_HitReact, "Ability.Shared.HitReact")
	UE_DEFINE_GAMEPLAY_TAG(Ability_Shared_Death, "Ability.Shared.Death")

	/** Attribute Tag **/
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Player_AttackPower, "Attribute.Player.AttackPower")
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Player_DefensePower, "Attribute.Player.DefensePower")
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Player_CriticalChance, "Attribute.Player.CriticalChance")
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Player_CriticalMagnitude, "Attribute.Player.CriticalMagnitude")
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Player_CurrentHealth, "Attribute.Player.CurrentHealth")
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Player_MaxHealth, "Attribute.Player.MaxHealth")
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Player_CurrentStamina, "Attribute.Player.CurrentStamina")
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Player_MaxStamina, "Attribute.Player.MaxStamina")
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Player_SwordAttackPower, "Attribute.Player.SwordAttackPower")
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Player_ShieldDefensePower, "Attribute.Player.ShieldDefensePower")
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Player_CharacterLevel, "Attribute.Player.CharacterLevel")
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Player_XP, "Attribute.Player.XP")
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Player_Recovery, "Attribute.Player.Recovery")
	UE_DEFINE_GAMEPLAY_TAG(Attribute_Player_LevelUp, "Attribute.Player.LevelUp")
	
	
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
	UE_DEFINE_GAMEPLAY_TAG(Event_HitReact_Front, "Event.HitReact.Front")
	UE_DEFINE_GAMEPLAY_TAG(Event_HitReact_Back, "Event.HitReact.Back")
	UE_DEFINE_GAMEPLAY_TAG(Event_HitReact_Left, "Event.HitReact.Left")
	UE_DEFINE_GAMEPLAY_TAG(Event_HitReact_Right, "Event.HitReact.Right")
	UE_DEFINE_GAMEPLAY_TAG(Event_HitPause, "Event.HitPause")
	
	UE_DEFINE_GAMEPLAY_TAG(Event_PerfectDodge, "Event.PerfectDodge")
	
	UE_DEFINE_GAMEPLAY_TAG(Event_SpawnProjectile, "Event.SpawnProjectile")
	
	UE_DEFINE_GAMEPLAY_TAG(Event_CharacterChange_One, "Event.CharacterChange.One")
	UE_DEFINE_GAMEPLAY_TAG(Event_CharacterChange_Two, "Event.CharacterChange.Two")
	UE_DEFINE_GAMEPLAY_TAG(Event_CharacterChange_Three, "Event.CharacterChange.Three")
	
	
	/* Block Tag */
	UE_DEFINE_GAMEPLAY_TAG(Block_Player_StaminaRegen, "Block.Player.StaminaRegen")
	UE_DEFINE_GAMEPLAY_TAG(Block_Player_Move, "Block.Player.Move")

	
	/** Class Tag **/
	UE_DEFINE_GAMEPLAY_TAG(CharacterClass_Player_Warrior, "CharacterClass.Player.Warrior")
	UE_DEFINE_GAMEPLAY_TAG(CharacterClass_Player_Knight, "CharacterClass.Player.Knight")
	UE_DEFINE_GAMEPLAY_TAG(CharacterClass_Player_Monk, "CharacterClass.Player.Monk")

	/** Item Tag **/
	UE_DEFINE_GAMEPLAY_TAG(Item_Sword, "Item.Sword")
	UE_DEFINE_GAMEPLAY_TAG(Item_Sword_BroadSword, "Item.Sword.BroadSword")
	UE_DEFINE_GAMEPLAY_TAG(Item_Sword_BlizzardRod, "Item.Sword.BlizzardRod")
	UE_DEFINE_GAMEPLAY_TAG(Item_Sword_SpikedBat, "Item.Sword.SpikedBat")
	
	UE_DEFINE_GAMEPLAY_TAG(Item_Shield, "Item.Shield")
	UE_DEFINE_GAMEPLAY_TAG(Item_Shield_DayBreaker, "Item.Shield.DayBreaker")
	UE_DEFINE_GAMEPLAY_TAG(Item_Shield_RoyalGuard, "Item.Shield.RoyalGuard")
	UE_DEFINE_GAMEPLAY_TAG(Item_Shield_SteelShield, "Item.Shield.SteelShield")
	
	UE_DEFINE_GAMEPLAY_TAG(Item_Eatable, "Item.Eatable")
	UE_DEFINE_GAMEPLAY_TAG(Item_Eatable_Apple, "Item.Eatable.Apple")
	UE_DEFINE_GAMEPLAY_TAG(Item_Eatable_Banana, "Item.Eatable.Banana")
	
	

}
