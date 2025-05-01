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

DECLARE_MULTICAST_DELEGATE(FOn)

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

	
	/** 주속성 **/
	UPROPERTY(BlueprintReadOnly, Category="Combat Attribute")
	FGameplayAttributeData AttackPower; /* 공격력 */
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, AttackPower);
	
	UPROPERTY(BlueprintReadOnly, Category="Combat Attribute")
	FGameplayAttributeData DefensePower; /* 방어력 */
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, DefensePower);
	
	UPROPERTY(BlueprintReadOnly, Category="Combat Attribute")
	FGameplayAttributeData CriticalChance; /* 치명타 확률 */
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, CriticalChance);
	
	UPROPERTY(BlueprintReadOnly, Category="Combat Attribute")
	FGameplayAttributeData CriticalMagnitude; /* 치명타 배율 */
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, CriticalMagnitude);
	
	UPROPERTY(BlueprintReadOnly, Category="Vital Attribute")
	FGameplayAttributeData CurrentHealth; /* 현재 체력 */
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, CurrentHealth);
	
	UPROPERTY(BlueprintReadOnly, Category="Vital Attribute")
	FGameplayAttributeData MaxHealth; /* 최대 체력 */
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, MaxHealth);
	
	UPROPERTY(BlueprintReadOnly, Category="Vital Attribute")
	FGameplayAttributeData CurrentStamina; /* 현재 기력 */
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, CurrentStamina);

	UPROPERTY(BlueprintReadOnly, Category="Vital Attribute")
	FGameplayAttributeData MaxStamina; /* 최대 기력 */
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, MaxStamina);

	/** 무기 공격력 **/
	UPROPERTY(BlueprintReadOnly, Category="Equipment Attribute")
	FGameplayAttributeData SwordAttackPower; /* 무기 공격력 */
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, SwordAttackPower);
	
	UPROPERTY(BlueprintReadOnly, Category="Equipment Attribute")
	FGameplayAttributeData ShieldDefensePower; /* 무기 공격력 */
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, ShieldDefensePower);

	
	/** 메타 데이터 속성  **/
	UPROPERTY(BlueprintReadOnly, Category="Meta Attribute")
	FGameplayAttributeData IncomingDamage;
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, IncomingDamage);

	UPROPERTY(BlueprintReadOnly, Category="Meta Attribute")
	FGameplayAttributeData IncomingStaminaCost;
	ATTRIBUTE_ACCESSORS(UAdventureAttributeSet, IncomingStaminaCost);
	
	
private:
	void SetEffectProperties(const FGameplayEffectModCallbackData& Data, FEffectProperties& Props);
	void HandleIncomingDamage(const FEffectProperties& Props);
	void ShowDamageText(const FEffectProperties& Props, const float Damage);
	void HandleInComingStaminaCost(const FEffectProperties& Props);
	
};
