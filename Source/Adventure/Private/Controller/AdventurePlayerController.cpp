// Cypie


#include "Controller/AdventurePlayerController.h"

#include "GameFramework/Character.h"
#include "UI/Widget/DamageTextComponent.h"

void AAdventurePlayerController::ShowDamageNumber(const float DamageAmount, ACharacter* TargetCharacter, const bool bIsCriticalHit, const FGameplayTag& DamageType)
{
	check(DamageTextClass)

	if (IsValid(TargetCharacter))
	{
		UDamageTextComponent* DamageTextComponent = NewObject<UDamageTextComponent>(TargetCharacter, DamageTextClass);
		DamageTextComponent->RegisterComponent();
		DamageTextComponent->AttachToComponent(TargetCharacter->GetRootComponent(), FAttachmentTransformRules::KeepRelativeTransform);
		DamageTextComponent->DetachFromComponent(FDetachmentTransformRules::KeepWorldTransform);
		DamageTextComponent->SetDamageText(DamageAmount, bIsCriticalHit, DamageType);
	}
	
}
