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