// Copyright Choi JinWoo. All Rights Reserved.


#include "AbilitySystem/Abilities/AdventureTargetLockAbility.h"

#include "AdventureFunctionLibrary.h"
#include "AdventureGameplayTag.h"
#include "Blueprint/UserWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Interface/CombatInterface.h"
#include "Kismet/KismetMathLibrary.h"

void UAdventureTargetLockAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                                  const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                                  const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);

	TryLockOnTarget();

	
}

void UAdventureTargetLockAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	CleanUp();
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UAdventureTargetLockAbility::OnTargetLockTick(float DeltaTime)
{
	if (!IsValid(ClosestActorToMouse) ||
		ICombatInterface::Execute_IsDead(GetAvatarActorFromActorInfo())
	)
	{
		CancelTargetLockAbility();
		return;
	}

	if (ICombatInterface::Execute_IsDead(ClosestActorToMouse))
	{
		TargetActors.Remove(ClosestActorToMouse);
		if (TargetActors.IsEmpty())
		{
			CancelTargetLockAbility();
			return;
		}
		ClosestActorToMouse = TargetActors.Last();
	}

	SetTargetLockWidgetPosition();

	const bool bShouldOverrideRotation =
		!UAdventureFunctionLibrary::DoseActorHaveTag(GetAvatarActorFromActorInfo(), AdventureGameplayTags::Status_Player_Dodging);

	if (bShouldOverrideRotation)
	{
		FRotator LookAtRot = UKismetMathLibrary::FindLookAtRotation(
			GetAvatarActorFromActorInfo()->GetActorLocation(),
			ClosestActorToMouse->GetActorLocation()
		);

		LookAtRot -= FRotator(TargetLockCameraOffsetDistance, 0.f, 0.f);

		const FRotator CurrentControlRot = CurrentActorInfo->PlayerController->GetControlRotation();
		const FRotator TargetRot = FMath::RInterpTo(CurrentControlRot, LookAtRot, DeltaTime, TargetLockRotationInterpSpeed);

		CurrentActorInfo->PlayerController->SetControlRotation(FRotator(TargetRot.Pitch, TargetRot.Yaw, 0.f));
		GetAvatarActorFromActorInfo()->SetActorRotation(FRotator(0.f, TargetRot.Yaw, 0.f));
		
	}

	
}

void UAdventureTargetLockAbility::TryLockOnTarget()
{
	FindClosestActorToMouse();
	
	if (TargetActors.IsEmpty() || !IsValid(ClosestActorToMouse))
	{
		CancelTargetLockAbility();
		return;
	}

	DrawTargetLockWidget();
	SetTargetLockWidgetPosition();
	
}

void UAdventureTargetLockAbility::FindClosestActorToMouse()
{
	float MouseX, MouseY;
	APlayerController* PlayerController = CurrentActorInfo->PlayerController.Get();
	
	if (!PlayerController->GetMousePosition(MouseX, MouseY)) return;

	FVector WorldLocation, WorldDirection;
	// DeprojectScreenPositionToWorld : 2D 좌표를 3D 월드의 위치와 방향으로 바꿔주는 함수
	if (!PlayerController->DeprojectScreenPositionToWorld(MouseX, MouseY, WorldLocation, WorldDirection)) return;

	const FVector CameraLocation = PlayerController->PlayerCameraManager->GetCameraLocation();
	const FVector TraceStart = WorldLocation;
	const FVector TraceEnd = WorldLocation + (WorldDirection * 5000);

	// 디버그: 마우스 광선 시각화
	if (bDrawDebugShape)
	{
		DrawDebugLine(GetWorld(), TraceStart, TraceEnd, FColor::Red, false, 2.0f, 0, 2.0f);
	}
	
	float MinDistance = FLT_MAX;

	TArray<AActor*> ActorsToIgnore;
	ActorsToIgnore.Add(GetAvatarActorFromActorInfo());

	UAdventureFunctionLibrary::GetLiveActorWithinRadius(
		GetAvatarActorFromActorInfo(),
		TargetActors,
		ActorsToIgnore,
		5000,
		GetAvatarActorFromActorInfo()->GetActorLocation()
	);

	if (TargetActors.IsEmpty())
	{
		return;
	}
		

	const FVector CharacterLocation = GetAvatarActorFromActorInfo()->GetActorLocation();
	const FVector ToCharacter = CharacterLocation - CameraLocation;

	for (AActor* TargetActor : TargetActors)
	{
		if (!IsValid(TargetActor)) continue;

		const FVector TargetLocation = TargetActor->GetActorLocation();
		FVector ClosestPoint = FMath::ClosestPointOnInfiniteLine(TraceStart, TraceEnd, TargetLocation);
		
		// 카메라에서 캐릭터 방향과, 카메라에서 타겟까지 방향 비교
		const FVector ToTarget = TargetLocation - CameraLocation;
		const float Dot = FVector::DotProduct(ToTarget.GetSafeNormal(), ToCharacter.GetSafeNormal());
		
		if (Dot < 0.0f)
		{
			// 카메라 기준으로 캐릭터 뒤에 있음 → 스킵
			continue;
		}
		
		const float DistToTarget = FVector::DistSquared(TargetActor->GetActorLocation(), ClosestPoint);

		// 디버그: 각 액터까지의 최근접 점 표시
		if (bDrawDebugShape)
		{
			DrawDebugSphere(GetWorld(), ClosestPoint, 20.0f, 12, FColor::Blue, false, 2.0f);
		}

		if (DistToTarget < MinDistance)
		{
			MinDistance = DistToTarget;
			ClosestActorToMouse = TargetActor;
		}
	}

	// 디버그: 마우스에서 가장 가까운 액터 위치 표시
	if (bDrawDebugShape && ClosestActorToMouse)
	{
		DrawDebugSphere(GetWorld(), ClosestActorToMouse->GetActorLocation(), 40.0f, 16, FColor::Green, false, 3.0f);
	}
	
}

void UAdventureTargetLockAbility::DrawTargetLockWidget()
{
	if (TargetLockWidget) return;
	
	check(TargetLockWidgetClass);

	TargetLockWidget = CreateWidget(CurrentActorInfo->PlayerController.Get(), TargetLockWidgetClass);
	check(TargetLockWidget);
	TargetLockWidget->AddToViewport();
	
}

void UAdventureTargetLockAbility::CancelTargetLockAbility()
{
	CancelAbility(GetCurrentAbilitySpecHandle(), GetCurrentActorInfo(), GetCurrentActivationInfo(), true);
}

void UAdventureTargetLockAbility::CleanUp()
{
	TargetActors.Empty();
	ClosestActorToMouse = nullptr;
	if (IsValid(TargetLockWidget))
	{
		TargetLockWidget->RemoveFromParent();
	}
	TargetLockWidget = nullptr;
	
}

void UAdventureTargetLockAbility::SetTargetLockWidgetPosition()
{
	if (!IsValid(TargetLockWidget) || !IsValid(ClosestActorToMouse))
	{
		CancelTargetLockAbility();
		return;
	}

	FVector2D ScreenPosition = FVector2D::ZeroVector;
	UWidgetLayoutLibrary::ProjectWorldLocationToWidgetPosition(
		CurrentActorInfo->PlayerController.Get(),
		ClosestActorToMouse->GetActorLocation(),
		ScreenPosition,
		true
	);

	TargetLockWidget->SetPositionInViewport(ScreenPosition, false);
	TargetLockWidget->SetAlignmentInViewport(FVector2D(0.5f, 1.f));
	
	
}
