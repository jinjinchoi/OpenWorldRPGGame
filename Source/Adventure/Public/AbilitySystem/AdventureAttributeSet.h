// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AdventureAttributeSet.generated.h"

#define ATTRIBUTE_ACCESSORS(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_PROPERTY_GETTER(ClassName, PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_GETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_SETTER(PropertyName) \
GAMEPLAYATTRIBUTE_VALUE_INITTER(PropertyName)

USTRUCT()
struct FEffectProperties
{
	GENERATED_BODY()

	FEffectProperties() {};
	
	FGameplayEffectContextHandle EffectContextHandle;

	UPROPERTY()
	UAbilitySystemComponent* SourceASC = nullptr;

	UPROPERTY()
	AActor* SourceAvatarActor = nullptr;

	UPROPERTY()
	AController* SourcePlayerController = nullptr;

	UPROPERTY()
	ACharacter* SourceCharacter = nullptr;

	UPROPERTY()
	UAbilitySystemComponent* TargetASC = nullptr;

	UPROPERTY()
	AActor* TargetAvatarActor = nullptr;

	UPROPERTY()
	AController* TargetPlayerController = nullptr;

	UPROPERTY()
	ACharacter* TargetCharacter = nullptr;
	
};

/**
 * 
 */
UCLASS()
class ADVENTURE_API UAdventureAttributeSet : public UAttributeSet
{
	GENERATED_BODY()

public:
	UAdventureAttributeSet();

	/* Begin UAttributeSet */
	virtual void PreAttributeChange(const FGameplayAttribute& Attribute, float& NewValue) override;
	virtual void PostGameplayEffectExecute(const struct FGameplayEffectModCallbackData& Data) override;
	/* End UAttributeSet */

	/* 공격력 */
	UPROPERTY(BlueprintReadOnly, Category="Combat Attribute")
	FGameplayAttributeData AttackPower;
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, AttackPower);

	/* 방어력 */
	UPROPERTY(BlueprintReadOnly, Category="Combat Attribute")
	FGameplayAttributeData DefensePower;
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, DefensePower);

	/* 치명타 확률 */
	UPROPERTY(BlueprintReadOnly, Category="Combat Attribute")
	FGameplayAttributeData CriticalChance;
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, CriticalChance);
	
	/* 치명타 배율 */
	UPROPERTY(BlueprintReadOnly, Category="Combat Attribute")
	FGameplayAttributeData CriticalMagnitude;
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, CriticalMagnitude);
	
	UPROPERTY(BlueprintReadOnly, Category="Vital Attribute")
	FGameplayAttributeData CurrentHealth;
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, CurrentHealth);
	
	UPROPERTY(BlueprintReadOnly, Category="Vital Attribute")
	FGameplayAttributeData MaxHealth;
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, Category="Vital Attribute")
	FGameplayAttributeData CurrentStamina;
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, CurrentStamina);

	UPROPERTY(BlueprintReadOnly, Category="Vital Attribute")
	FGameplayAttributeData MaxStamina;
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, MaxStamina);

private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
	
};
