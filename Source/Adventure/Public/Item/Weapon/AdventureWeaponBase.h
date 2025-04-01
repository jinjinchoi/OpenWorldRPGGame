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
	void ToggleCollisionEnable(const bool bIsEnable);

protected:
	virtual void BeginPlay() override;

	UFUNCTION()
	void CollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);

	UFUNCTION()
	void CollisionBoxEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon Data")
	TObjectPtr<UStaticMeshComponent> WeaponMesh;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category="Weapon Data")
	TObjectPtr<UBoxComponent> WeaponCollisionBox;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category="Weapon Data")
	bool bIsPlayerWeapon = false;

private:
	TArray<TObjectPtr<AActor>> OverlappedActors;
	
};
