// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AdventurePlayerState.generated.h"

class AAdventurePlayerCharacter;
/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventurePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void RegisterPartyMember(const int32 PartyIndex, AAdventurePlayerCharacter* PartyMember, const bool bIsCurrentlyPlaying = false);
	void SetCurrentControlCharacterIndex(const int32 InPartyIndex);

	AAdventurePlayerCharacter* GetCurrentControlCharacter();
	
protected:
	TMap<int32, AAdventurePlayerCharacter*> PartyCharacterMap;
	
	int32 CurrentControlCharacterIndex;

	
	
};
