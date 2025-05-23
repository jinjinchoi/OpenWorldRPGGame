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
}

bool AAdventureBaseCharacter::IsDead_Implementation() const
{
	return bIsDead;
}

void AAdventureBaseCharacter::OnCharacterDied_Implementation()
{
	bIsDead = true;
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	
}

int32 AAdventureBaseCharacter::GetCharacterLevel() const
{
	const UAdventureAttributeSet* AdventureAttributeSet = Cast<UAdventureAttributeSet>(AttributeSet);
	check(AdventureAttributeSet);

	return AdventureAttributeSet->GetCharacterLevel();
}

void AAdventureBaseCharacter::RegisterSpawnedWeapon(AAdventureWeaponBase* InWeaponToRegister)
{
	check(InWeaponToRegister);
	OwningWeapon = InWeaponToRegister;

}

void AAdventureBaseCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (IsValid(AbilitySystemComponent) && !IsActorBeingDestroyed())
	{
		AbilitySystemComponent->InitAbilityActorInfo(this, this);
	}
	
	
}

void AAdventureBaseCharacter::Destroyed()
{
	Super::Destroyed();

	if (OwningWeapon)
	{
		OwningWeapon->Destroy();
	}
}

void AAdventureBaseCharacter::OnHitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	bIsHitReacting = NewCount > 0;
}
