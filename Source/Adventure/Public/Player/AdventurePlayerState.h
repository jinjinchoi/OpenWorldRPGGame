// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "AdventurePlayerState.generated.h"

class UControllableCharacterManager;
class ACharacter;
/**
 * 
 */
UCLASS()
class ADVENTURE_API AAdventurePlayerState : public APlayerState
{
	GENERATED_BODY()

public:
	void AddCharacterToPartyMember(ACharacter* CharacterToAdd, const int32 MemberIndex) const;
	UControllableCharacterManager* GetControllableCharacterManager();

protected:
	virtual void BeginPlay() override;
	
	UPROPERTY()
	TObjectPtr<UControllableCharacterManager> ControllableCharacterManager;

	UPROPERTY(EditDefaultsOnly, Category="Test")
	TMap<TSubclassOf<ACharacter>, int32> TestPartyMembers;
	
	
	
};
