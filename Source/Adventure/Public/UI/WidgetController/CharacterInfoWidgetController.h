// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AdventureType/AdventureStructTypes.h"
#include "UI/WidgetController/AdventureWidgetControllerBase.h"
#include "CharacterInfoWidgetController.generated.h"

class AAdventurePlayerState;

DECLARE_DYNAMIC_MULTICAST_DELEGATE_OneParam(FOnGetOwningCharacterInfoDelegate, const FPartyCharacterInfo&, OwningCharacterInfo);

/**
 * 
 */
UCLASS()
class ADVENTURE_API UCharacterInfoWidgetController : public UAdventureWidgetControllerBase
{
	GENERATED_BODY()

public:
	/* Begin WidgetController Base */
	virtual void BroadCastInitialValue() override;
	/* End WidgetController Base */

	UFUNCTION(BlueprintCallable)
	TArray<FPartyCharacterInfo> GetOwningCharactersInfo();

	UFUNCTION(BlueprintCallable)
	TMap<int32, FPartyCharacterInfo> GetPartyMemberInfo();
	
	UFUNCTION(BlueprintCallable)
	bool AddToPartyMember (const FGameplayTag& CharacterTagToAdd, const int32 PartyIndexToAdd);
	
	UFUNCTION(BlueprintCallable)
	bool RemoveFromPartyMemberByPartyIndex(const int32 PartyIndexToRemove);

	UFUNCTION(BlueprintCallable)
	bool RemoveFromPartyMemberByClassTag(const FGameplayTag& CharacterTagToRemove);
	
	UPROPERTY(BlueprintAssignable)
	FOnGetOwningCharacterInfoDelegate GetOwningCharacterInfoDelegate;

	

	
protected:
	UFUNCTION(BlueprintCallable, Category="Character")
	FPartyCharacterInfo GetOwningCharacterInfoByClassTag(const FGameplayTag& ClassTag);

private:
	UPROPERTY()
	TObjectPtr<AAdventurePlayerState> AdventurePlayerState;

	bool ChangePlayCharacterIfPossible();


public:
	AAdventurePlayerState* GetAdventurePlayerState();
};
