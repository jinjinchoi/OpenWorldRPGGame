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
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Climb_Stop);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Climb_Move);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Climb_Hop);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_NormalAbility);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_SpecialAbility);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_ESkill);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_RSkill);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_ChangeCharacter_One);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_ChangeCharacter_Two);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_ChangeCharacter_Three);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Interaction);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_OpenMenu);
	
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(InputTag_Toggleable_TargetLock);

	
	/** Status Tag **/
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Locomotion_Sprint);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Locomotion_Falling);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Locomotion_Climbing);
	
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_CanHeavyAttack);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_HeavyAttackActive);
	
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_HitReact);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Dead);

	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Player_Dodging);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Player_CanCounterAttack);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Player_TargetLock);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Player_CombatAbilityActivated);
	
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Enemy_Strafing);
	
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Shared_Invincible);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Status_Shared_SuperArmor);
	
	
	/** Ability Tag **/
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_Attack_Normal);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_Attack_Heavy);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_Dodge);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_HitPause);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_PerfectDodge);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_TargetLock);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_ESkill);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_RSkill);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Player_CharacterChange);
	
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Enemy_Attack_Melee);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Enemy_Attack_Ranged);

	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Shared_HitReact);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Ability_Shared_Death);

	/** Attribute Tag **/
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Player_AttackPower);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Player_DefensePower);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Player_CriticalChance);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Player_CriticalMagnitude);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Player_CurrentHealth);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Player_MaxHealth);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Player_CurrentStamina);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Player_MaxStamina);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Player_SwordAttackPower);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Player_ShieldDefensePower);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Player_CharacterLevel);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Player_XP);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Player_Recovery);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Attribute_Player_LevelUp);
	
	
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
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_HitReact_Front);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_HitReact_Back);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_HitReact_Left);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_HitReact_Right);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_HitPause);

	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_PerfectDodge); 
	
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_SpawnProjectile);
	
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_CharacterChange_One);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_CharacterChange_Two);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Event_CharacterChange_Three);

	
	/** Block Tag **/
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Block_Player_StaminaRegen);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Block_Player_Move);

	
	/** Class Tag **/
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(CharacterClass_Player_Warrior);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(CharacterClass_Player_Knight);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(CharacterClass_Player_Monk);

	/** Item Tag **/
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Sword);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Sword_BroadSword);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Sword_BlizzardRod);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Sword_SpikedBat);
	
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Shield);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Shield_DayBreaker);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Shield_RoyalGuard);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Shield_SteelShield);
	
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Eatable);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Eatable_Apple);
	ADVENTURE_API UE_DECLARE_GAMEPLAY_TAG_EXTERN(Item_Eatable_Banana);

	
	
	

}
