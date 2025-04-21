// Copyright Choi JinWoo. All Rights Reserved.


#include "AbilitySystem/Abilities/AdventureChangeCharacterAbility.h"
#include "Player/AdventurePlayerState.h"

void UAdventureChangeCharacterAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);

	CharacterManager = nullptr;
}

void UAdventureChangeCharacterAbility::OnCharacterChangeAbilityActivated()
{
	if (CharacterManager) return;
	
	if (const APlayerController* PC = CurrentActorInfo->PlayerController.Get())
	{
		if (AAdventurePlayerState* AdventurePlayerState = Cast<AAdventurePlayerState>(PC->PlayerState))
		{
			CharacterManager = AdventurePlayerState->GetControllableCharacterManager();
		}
	}

	
}

void UAdventureChangeCharacterAbility::SpawnNewCharacterAndRemoveOldCharacter(int32 InCharacterIndex)
{

}
