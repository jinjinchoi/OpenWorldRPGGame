// Copyright Choi JinWoo. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "AdventureWeaponBase.generated.h"

class UBoxComponent;

UCLASS()
class ADVENTURE_API AAdventureWeaponBase : public AActor
{
	GENERATED_BODY()
	
public:	
	AAdventureWeaponBase();

protected:
	virtual void BeginPlay() override;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon Data")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon Data")
	TObjectPtr<UBoxComponent> WeaponCollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon Data")
	bool bIsPlayerWeapon = false;

public:
	FORCEINLINE UBoxComponent* GetWeaponCollisionBox() const { return WeaponCollisionBox; }
	
};
