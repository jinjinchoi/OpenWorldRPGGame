// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "GameplayEffectTypes.h"
#include "AdventureAbilityTypes.generated.h"

USTRUCT(BlueprintType)
struct FAdventureGameplayEffectContext : public FGameplayEffectContext
{
	GENERATED_BODY()

public:
	virtual UScriptStruct* GetScriptStruct() const override
	{
		return StaticStruct();
	}

	virtual FAdventureGameplayEffectContext* Duplicate() const override
	{
		FAdventureGameplayEffectContext* NewContext = new FAdventureGameplayEffectContext();
		*NewContext = *this;
		if (GetHitResult())
		{
			NewContext->AddHitResult(*GetHitResult(), true);
		}
		return NewContext;
	}

	virtual bool NetSerialize(FArchive& Ar, class UPackageMap* Map, bool& bOutSuccess) override;

	bool IsCriticalHit () const { return bIsCriticalHit; }
	TSharedPtr<FGameplayTag> GetDamageType() const { return DamageType;}
	FVector GetKnockBackDirection() const { return KnockBackDirection; }
	
	void SetIsCriticalHit(const bool bInIsCriticalHit) { bIsCriticalHit = bInIsCriticalHit; }
	void SetDamageType(const TSharedPtr<FGameplayTag>& InDamageType) { DamageType = InDamageType; }
	void SetKnockBackDirection(const FVector& InDirection ) { KnockBackDirection = InDirection; }

protected:
	UPROPERTY()
	bool bIsCriticalHit = false;

	TSharedPtr<FGameplayTag> DamageType;

	UPROPERTY()
	FVector KnockBackDirection = FVector::ZeroVector;
	
	
};

template<>
struct TStructOpsTypeTraits<FAdventureGameplayEffectContext> : public TStructOpsTypeTraitsBase2<FAdventureGameplayEffectContext>
{
	enum
	{
		WithNetSerializer = true,
		WithCopy = true
	};
};
