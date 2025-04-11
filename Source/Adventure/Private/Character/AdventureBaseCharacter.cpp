// Copyright Choi JinWoo. All Rights Reserved.


#include "Character/AdventureBaseCharacter.h"

#include "AbilitySystem/AdventureAbilitySystemComponent.h"
#include "AbilitySystem/AdventureAttributeSet.h"
#include "Component/Movement/AdventureMovementComponent.h"
#include "Item/Weapon/AdventureWeaponBase.h"
#include "MotionWarpingComponent.h"
#include "Components/CapsuleComponent.h"


AAdventureBaseCharacter::AAdventureBaseCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer.SetDefaultSubobjectClass<UAdventureMovementComponent>(ACharacter::CharacterMovementComponentName))
{

	PrimaryActorTick.bCanEverTick = false;
	PrimaryActorTick.bStartWithTickEnabled = false;

	GetMesh()->bReceivesDecals = false;
	GetMesh()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);
	GetCapsuleComponent()->SetCollisionResponseToChannel(ECC_Camera, ECR_Ignore);

	AbilitySystemComponent = CreateDefaultSubobject<UAdventureAbilitySystemComponent>("AbilitySystemComponent");
	AttributeSet = CreateDefaultSubobject<UAdventureAttributeSet>("AttributeSet");

	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>("MotionWarpingComponent");

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

bool AAdventureBaseCharacter::IsDead() const
{
	return bIsDead;
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

void AAdventureBaseCharacter::OnHitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bIsHitReacting = NewCount > 0;
}

void AAdventureBaseCharacter::OnDeathReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bIsDead = NewCount > 0;
}
