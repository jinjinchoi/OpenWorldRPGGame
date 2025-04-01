// Copyright Choi JinWoo. All Rights Reserved.


#include "Character/AdventureBaseCharacter.h"

#include "AbilitySystem/AdventureAbilitySystemComponent.h"
#include "AbilitySystem/AdventureAttributeSet.h"
#include "Item/Weapon/AdventureWeaponBase.h"


AAdventureBaseCharacter::AAdventureBaseCharacter()
{

	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;

	AbilitySystemComponent = CreateDefaultSubobject<UAdventureAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UAdventureAttributeSet>("AttributeSet");

}

UAbilitySystemComponent* AAdventureBaseCharacter::GetAbilitySystemComponent() const
{
	return AbilitySystemComponent;
}

void AAdventureBaseCharacter::ToggleWeaponCollision_Implementation(const bool bIsEnable, const EAdventureWeaponType AdventureWeaponType)
{
	if (AdventureWeaponType == EAdventureWeaponType::Weapon && OwningWeapon)
	{
		OwningWeapon->ToggleCollisionEnable(bIsEnable);
	}
	else
	{
		
	}
}

void AAdventureBaseCharacter::RegisterSpawnedWeapon(AAdventureWeaponBase* InWeaponToRegister)
{
	check(InWeaponToRegister);
	OwningWeapon = InWeaponToRegister;

}

void AAdventureBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (AbilitySystemComponent)
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	
	
}
