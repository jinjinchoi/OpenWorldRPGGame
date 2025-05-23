// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

UENUM()
enum class EAdventureWeaponType : uint8
{
	Weapon,
	LeftHand,
	RightHand
};

UENUM(BlueprintType)
namespace ECustomMovementMode
{
	enum Type
	{
		MOVE_Climb UMETA(DisplayName = "Climb Mode"),
	};
}

UENUM(BlueprintType)
enum class ECharacterMovementType : uint8
{
	Normal,
	Climb
};

UENUM(BlueprintType)
enum class EEquipmentItemType : uint8
{
	Sword,
	Shield
};
