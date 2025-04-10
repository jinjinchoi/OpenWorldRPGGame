// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "UObject/NoExportTypes.h"
#include "ControllableCharacterManager.generated.h"

class ACharacter;
/**
 * 
 */
UCLASS()
class ADVENTURE_API UControllableCharacterManager : public UObject
{
	GENERATED_BODY()

public:
	void RegisterPartyMember(ACharacter* CharacterToAdd, int32 PartyIndex);
	
	
protected:
	TMap<int32, ACharacter*> PartyMemberMap;

	int32 CurrentPartyMemberIndex = 1;
	
	
};
