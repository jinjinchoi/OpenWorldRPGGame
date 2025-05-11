// Copyright Choi JinWoo. All Rights Reserved.


#include "Character/AdventurePlayerCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AdventureFunctionLibrary.h"
#include "AdventureGameplayTag.h"
#include "DebugHelper.h"
#include "Camera/CameraComponent.h"
#include "AbilitySystem/AdventureAbilitySystemComponent.h"
#include "AbilitySystem/AdventureAttributeSet.h"
#include "Component/Input/AdventureInputComponent.h"
#include "Component/Movement/AdventureMovementComponent.h"
#include "Controller/AdventurePlayerController.h"
#include "DataAsset/Item/DataAsset_ItemInfo.h"
#include "DataAsset/StartUpData/DataAsset_StartUpData_Player.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameManager/ControllableCharacterManager.h"
#include "Item/Pickups/AdventureInventoryItem.h"
#include "Player/AdventureInventory.h"
#include "Player/AdventurePlayerState.h"
#include "UI/HUD/AdventureInGameHUD.h"

AAdventurePlayerCharacter::AAdventurePlayerCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;
	
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("CameraBoom"));
	CameraBoom->SetupAttachment(GetRootComponent());
	CameraBoom->TargetArmLength = 500.f;
	CameraBoom->SocketOffset = FVector(0.f, 0.f, 60.f);
	CameraBoom->bUsePawnControlRotation = true;

	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("FollowCamera"));
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;

	AdventureMovementComponent = Cast<UAdventureMovementComponent>(GetCharacterMovement());

	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 500.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;
	
}


void AAdventurePlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	if (AdventureMovementComponent)
	{
		AdventureMovementComponent->OnEnterClimbStateDelegate.BindUObject(this, &AAdventurePlayerCharacter::OnPlayerEnterClimbState);
		AdventureMovementComponent->OnExitClimbStateDelegate.BindUObject(this, &AAdventurePlayerCharacter::OnPlayerExitClimbState);
	}
	
}


void AAdventurePlayerCharacter::ShowWeaponMesh_Implementation()
{
	SetWeaponMeshVisibility(true);
}

void AAdventurePlayerCharacter::HideWeaponMesh_Implementation()
{
	SetWeaponMeshVisibility(false);
}

void AAdventurePlayerCharacter::OnStaminaDepleted()
{
	if (bIsSprint)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		bIsSprint = false;
		GetWorld()->GetTimerManager().ClearTimer(SprintTimerHandle);
		UAdventureFunctionLibrary::RemoveGameplayTagToActorIfFound(this, AdventureGameplayTags::Status_Locomotion_Sprint);
	}
	if (AdventureMovementComponent->IsClimbing())
	{
		bool Unnecessary = false; 
		AdventureMovementComponent->ToggleClimbing(false, Unnecessary);
	}
	
	RemoveStaminaCostEffect();
}

void AAdventurePlayerCharacter::PickUpItemBeginOverlap(AAdventureInventoryItem* InOverlappedItem)
{
	OverlappedItems.AddUnique(InOverlappedItem);
	OnOverlappedItemChangedDelegate.ExecuteIfBound(OverlappedItems);

}

void AAdventurePlayerCharacter::PickUpItemEndOverlap(AAdventureInventoryItem* InOverlappedItem)
{
	for (int32 i = OverlappedItems.Num() - 1; i >= 0; --i)
	{
		if (!OverlappedItems[i].IsValid())
		{
			OverlappedItems.RemoveAt(i);
		}
	}

	OverlappedItems.Remove(InOverlappedItem);
	OnOverlappedItemChangedDelegate.ExecuteIfBound(OverlappedItems);
	
}

void AAdventurePlayerCharacter::OnCharacterDied_Implementation()
{
	Super::OnCharacterDied_Implementation();

	bool Unnecessary = false;
	AdventureMovementComponent->ToggleClimbing(false, Unnecessary);
}


void AAdventurePlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	AAdventurePlayerState* AdventurePlayerState = Cast<AAdventurePlayerState>(GetPlayerState());
	check(AdventurePlayerState);

	if (AdventurePlayerState->bIsPlayerStateSet)
	{
		InitPlayerCharacterData();
	}
	else
	{
		AdventurePlayerState->OnPlayerStateSetDelegate.AddUObject(this, &ThisClass::InitPlayerCharacterData);
	}
	
	BindGameplayTagChanged();
	
}


void AAdventurePlayerCharacter::InitPlayerCharacterData()
{
	if (!CharacterStartUpData)
	{
		DebugHelper::Print(FString::Printf(TEXT("You need to assign startup data to %s"), *GetName()), FColor::Red);
		return;
	}
	if (!CharacterTag.IsValid())
	{
		DebugHelper::Print(FString::Printf(TEXT("You need to assign Character Tag to %s"), *GetName()), FColor::Yellow);
	}
	
	UAdventureAbilitySystemComponent* AdventureAbilitySystemComponent = Cast<UAdventureAbilitySystemComponent>(AbilitySystemComponent);
	check(AdventureAbilitySystemComponent);

	AAdventurePlayerState* AdventurePlayerState = Cast<AAdventurePlayerState>(GetPlayerState());
	const FPartyCharacterInfo CurrentCharacterInfo = *AdventurePlayerState->GetControllableCharacterManager()->FindCharacterInfoInOwningCharacters(CharacterTag);
	check(CurrentCharacterInfo.IsValid());

	// Attribute 부여
	CharacterStartUpData->GrantCharacterLevelEffect(AdventureAbilitySystemComponent, CurrentCharacterInfo.CharacterLevel);
	CharacterStartUpData->GrantStartUpGameplayEffect(AdventureAbilitySystemComponent);
	CharacterStartUpData->ApplySetByCallerEffectByCharacterInfo(AdventureAbilitySystemComponent, CurrentCharacterInfo);

	// Ability 부여
	CharacterStartUpData->GiveToAbilitySystemComponent(AdventureAbilitySystemComponent);
	AdventureAbilitySystemComponent->InitializeAbilityFromCharacterInfo(CurrentCharacterInfo);

	// 무기 능력치 부여
	ApplyEquipmentEffect(CurrentCharacterInfo.WeaponTag);
	ApplyEquipmentEffect(CurrentCharacterInfo.ShieldTag);

	// 오버레이 초기화
	if (AAdventurePlayerController* PlayerController = Cast<AAdventurePlayerController>(GetController()))
	{
		if (AAdventureInGameHUD* AdventureInGameHUD = Cast<AAdventureInGameHUD>(PlayerController->GetHUD()))
		{
			AdventureInGameHUD->InitOverlay(PlayerController, GetPlayerState(), AbilitySystemComponent, AttributeSet, CharacterTag);
		}
	}
	
}


void AAdventurePlayerCharacter::InitPlayerStartUpData() const
{
	if (!CharacterStartUpData)
	{
		DebugHelper::Print(FString::Printf(TEXT("You need to assign startup data to %s"), *GetName()), FColor::Red);
		return;
	}
	if (!CharacterTag.IsValid())
	{
		DebugHelper::Print(FString::Printf(TEXT("You need to assign Character Tag to %s"), *GetName()), FColor::Yellow);
	}
	
	UAdventureAbilitySystemComponent* AdventureAbilitySystemComponent = Cast<UAdventureAbilitySystemComponent>(AbilitySystemComponent);
	check(AdventureAbilitySystemComponent);
		
	CharacterStartUpData->GiveToAbilitySystemComponent(AdventureAbilitySystemComponent);
	CharacterStartUpData->GrantStartUpGameplayEffect(AdventureAbilitySystemComponent);

}

void AAdventurePlayerCharacter::BindGameplayTagChanged()
{
	if (!AbilitySystemComponent) return;

	AbilitySystemComponent->RegisterGameplayTagEvent(AdventureGameplayTags::Status_HitReact, EGameplayTagEventType::NewOrRemoved)
		.AddUObject(this, &ThisClass::OnHitReactTagChanged);
}

void AAdventurePlayerCharacter::AddCharacterInfoToManager() const
{
	const FPartyCharacterInfo CharacterInfo = UAdventureFunctionLibrary::MakePartyCharacterInfo(this, false, true);
	
	if (AAdventurePlayerState* AdventurePlayerState = Cast<AAdventurePlayerState>(GetPlayerState()))
	{
		AdventurePlayerState->GetControllableCharacterManager()->AddOrUpdatePartyCharactersInfo(CurrentCharacterIndex, CharacterInfo);
	}
}

void AAdventurePlayerCharacter::ApplyRecoveryEffect(const float RecoveryAmount) const
{
	check(RecoveryEffect);

	if (RecoveryAmount <= 0) return;

	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(RecoveryEffect, 1.f, ContextHandle);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, AdventureGameplayTags::Attribute_Player_Recovery, RecoveryAmount);

	AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	
}

void AAdventurePlayerCharacter::OnHitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	Super::OnHitReactTagChanged(CallbackTag, NewCount);
	
	if (bIsHitReacting)
	{
		bool Unnecessary = false;
		AdventureMovementComponent->ToggleClimbing(false, Unnecessary);
	}
	
}

bool AAdventurePlayerCharacter::ApplyStaminaCostEffect(const TSubclassOf<UGameplayEffect>& InEffect)
{
	check(InEffect);

	float StaminaCost = 0.f;
	for (const FGameplayModifierInfo& Modifier : InEffect->GetDefaultObject<UGameplayEffect>()->Modifiers)
	{
		if (Modifier.Attribute == UAdventureAttributeSet::GetIncomingStaminaCostAttribute())
		{
			Modifier.ModifierMagnitude.GetStaticMagnitudeIfPossible(1.f, StaminaCost);
		}
	}

	if (StaminaCost == 0.f) return true;

	const UAdventureAttributeSet* AdventureAttributeSet = Cast<UAdventureAttributeSet>(AttributeSet);
	check(AdventureAttributeSet);

	if (AdventureAttributeSet->GetCurrentStamina() < StaminaCost)
	{
		return false;
	}

	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);

	if (InEffect->GetDefaultObject<UGameplayEffect>()->DurationPolicy == EGameplayEffectDurationType::Instant)
	{
		AbilitySystemComponent->ApplyGameplayEffectToSelf(InEffect->GetDefaultObject<UGameplayEffect>(), 1.f, ContextHandle);
	}
	else
	{
		StaminaCostEffectHandle = AbilitySystemComponent->ApplyGameplayEffectToSelf(InEffect->GetDefaultObject<UGameplayEffect>(), 1.f, ContextHandle);
	}

	UAdventureFunctionLibrary::AddGameplayTagToActorIfNone(this, AdventureGameplayTags::Block_Player_StaminaRegen);
	
	return true;
	
}

void AAdventurePlayerCharacter::RemoveStaminaCostEffect()
{
	if (!bIsSprint)
	{
		AbilitySystemComponent->RemoveActiveGameplayEffect(StaminaCostEffectHandle);
		UAdventureFunctionLibrary::RemoveGameplayTagToActorIfFound(this, AdventureGameplayTags::Block_Player_StaminaRegen);
	}
	
}


void AAdventurePlayerCharacter::ApplyEquipmentEffect(const FGameplayTag& EquipmentTag)
{
	check(AbilitySystemComponent && EquipmentDataAsset && SwordGameplayEffect && ShieldGameplayEffect);
	
	if (!EquipmentTag.IsValid()) return;

	bool bIsSwordItem = true;

	if (EquipmentTag.MatchesTag(AdventureGameplayTags::Item_Shield))
	{
		bIsSwordItem = false;
	}
	
	RemoveEquipmentEffect(bIsSwordItem);
	
	const FItemInfoParams ItemData = EquipmentDataAsset->FindItemInfo(EquipmentTag);
	FGameplayEffectContextHandle ContextHandle = AbilitySystemComponent->MakeEffectContext();
	ContextHandle.AddSourceObject(this);
	
	const FGameplayEffectSpecHandle SpecHandle = AbilitySystemComponent->MakeOutgoingSpec(
		bIsSwordItem ? SwordGameplayEffect : ShieldGameplayEffect,
		1.f,
		ContextHandle);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, AdventureGameplayTags::Attribute_Player_SwordAttackPower, ItemData.AttackPower);
	UAbilitySystemBlueprintLibrary::AssignTagSetByCallerMagnitude(SpecHandle, AdventureGameplayTags::Attribute_Player_DefensePower, ItemData.DefensePower);

	if (bIsSwordItem)
	{
		EquippedSwordTag = EquipmentTag;
		SwordActiveGameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
	else
	{
		EquippedShieldTag = EquipmentTag;
		ShieldActiveGameplayEffectHandle = AbilitySystemComponent->ApplyGameplayEffectSpecToSelf(*SpecHandle.Data.Get());
	}
	
	
}

void AAdventurePlayerCharacter::RemoveEquipmentEffect(const bool bIsSwordEffect) const
{
	check(AbilitySystemComponent);
	
	if (bIsSwordEffect && SwordActiveGameplayEffectHandle.IsValid())
	{
		AbilitySystemComponent->RemoveActiveGameplayEffect(SwordActiveGameplayEffectHandle);
	}
	else if (ShieldActiveGameplayEffectHandle.IsValid())
	{
		AbilitySystemComponent->RemoveActiveGameplayEffect(ShieldActiveGameplayEffectHandle);
	}
}


#pragma region Input

void AAdventurePlayerCharacter::Input_Look(const FInputActionValue& InputActionValue)
{
	const FVector2D LookAxisVector = InputActionValue.Get<FVector2D>();

	if (LookAxisVector.X != 0.f)
	{
		AddControllerYawInput(LookAxisVector.X);
	}

	if (LookAxisVector.Y != 0.f)
	{
		AddControllerPitchInput(LookAxisVector.Y);
	}
}

void AAdventurePlayerCharacter::Input_CameraScroll(const FInputActionValue& InputActionValue)
{
	const float ScrollValue = InputActionValue.Get<float>() * -CameraZoomSpeed;
	
	float NewTargetArmLength =  CameraBoom->TargetArmLength + ScrollValue;
	NewTargetArmLength = FMath::Clamp(NewTargetArmLength, 150.f, 800.f);
	
	CameraBoom->TargetArmLength = FMath::FInterpTo(CameraBoom->TargetArmLength, NewTargetArmLength, GetWorld()->GetDeltaSeconds(), 10.0f);
}

void AAdventurePlayerCharacter::Input_Move(const FInputActionValue& InputActionValue)
{
	if (bIsHitReacting || bIsDead)
	{
		Input_StopMove();
		return;
	}
	
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FRotator MovementRotation(0.f, Controller->GetControlRotation().Yaw, 0.f);

	if (MovementVector.Y >= 0)
	{
		TryClimbAction();
	}

	if (MovementVector.Y != 0.f)
	{
		const FVector ForwardDirection = MovementRotation.RotateVector(FVector::ForwardVector);
		AddMovementInput(ForwardDirection, MovementVector.Y);
	}

	if (MovementVector.X != 0.f)
	{
		const FVector RightDirection = MovementRotation.RotateVector(FVector::RightVector);
		AddMovementInput(RightDirection, MovementVector.X);
	}
}

void AAdventurePlayerCharacter::Input_StopMove()
{
	if (bIsSprint)
	{
		StopSprint();
	}
}

void AAdventurePlayerCharacter::Input_ClimbMovement(const FInputActionValue& InputActionValue)
{
	const FVector2D MovementVector = InputActionValue.Get<FVector2D>();
	const FVector ForwardDirection = FVector::CrossProduct(
		-AdventureMovementComponent->GetClimbableSurfaceNormal(),
		GetActorRightVector()
	);

	const FVector RightDirection = FVector::CrossProduct(
		-AdventureMovementComponent->GetClimbableSurfaceNormal(),
		-GetActorUpVector()
	);

	AddMovementInput(ForwardDirection, MovementVector.Y);
	AddMovementInput(RightDirection, MovementVector.X);
	
}


void AAdventurePlayerCharacter::Input_Sprint_Started()
{
	GetWorld()->GetTimerManager().SetTimer(SprintTimerHandle, this, &AAdventurePlayerCharacter::StartSprint, 0.5f, false);
}

void AAdventurePlayerCharacter::Input_Sprint_Completed()
{
	if (!bIsSprint)
	{
		GetWorld()->GetTimerManager().ClearTimer(SprintTimerHandle);
	}
}

void AAdventurePlayerCharacter::StartSprint()
{
	if (!ApplyStaminaCostEffect(RunAndClimbCostEffectClass))
	{
		return;
	}
	
	GetCharacterMovement()->MaxWalkSpeed = SprintSpeed;
	bIsSprint = true;
	bIsWalking = false;
	
	UAdventureFunctionLibrary::AddGameplayTagToActorIfNone(this, AdventureGameplayTags::Status_Locomotion_Sprint);
}

void AAdventurePlayerCharacter::StopSprint()
{
	GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
	bIsSprint = false;
	GetWorld()->GetTimerManager().ClearTimer(SprintTimerHandle);

	UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
	if (AnimInstance && RunToStopMontage && !GetCharacterMovement()->IsFalling())
	{
		AnimInstance->Montage_Play(RunToStopMontage);
	}
	
	RemoveStaminaCostEffect();
	UAdventureFunctionLibrary::RemoveGameplayTagToActorIfFound(this, AdventureGameplayTags::Status_Locomotion_Sprint);
}

void AAdventurePlayerCharacter::Input_Walk()
{
	if (bIsWalking)
	{
		GetCharacterMovement()->MaxWalkSpeed = RunSpeed;
		bIsWalking = false;
	}
	else
	{
		GetCharacterMovement()->MaxWalkSpeed = WalkingSpeed;
		bIsWalking = true;
		bIsSprint = false;
	}

	RemoveStaminaCostEffect();
	UAdventureFunctionLibrary::RemoveGameplayTagToActorIfFound(this, AdventureGameplayTags::Status_Locomotion_Sprint);
}


void AAdventurePlayerCharacter::Input_Jump()
{
	Super::Jump();
}

void AAdventurePlayerCharacter::Input_AbilityInputPressed(const FGameplayTag& InInputTag)
{
	if (AdventureMovementComponent && AdventureMovementComponent->IsClimbing()) return;
	
	if (UAdventureAbilitySystemComponent* AdventureASC = Cast<UAdventureAbilitySystemComponent>(AbilitySystemComponent))
	{
		AdventureASC->OnAbilityInputPressed(InInputTag);
	}
}

void AAdventurePlayerCharacter::Input_AbilityInputReleased(const FGameplayTag& InInputTag)
{
	if (AdventureMovementComponent && AdventureMovementComponent->IsClimbing()) return;
	
	if (UAdventureAbilitySystemComponent* AdventureASC = Cast<UAdventureAbilitySystemComponent>(AbilitySystemComponent))
	{
		AdventureASC->OnAbilityInputReleased(InInputTag);
	}
}

void AAdventurePlayerCharacter::TryClimbAction()
{
	if (!AdventureMovementComponent) return;
	bool bIsClimbStarted = false;
	
	if (!AdventureMovementComponent->IsClimbing())
	{
		AdventureMovementComponent->ToggleClimbing(true, bIsClimbStarted);
	}
	if (bIsClimbStarted)
	{
		ApplyStaminaCostEffect(RunAndClimbCostEffectClass);
	}
}

void AAdventurePlayerCharacter::Input_ClimbActionCompleted()
{
	if (!AdventureMovementComponent) return;

	if (AdventureMovementComponent->IsClimbing())
	{
		bool Unnecessary = false;
		AdventureMovementComponent->ToggleClimbing(false, Unnecessary);
	}
}

void AAdventurePlayerCharacter::Input_ClimbHopActionStarted(const FInputActionValue& InputActionValue)
{

	if (AdventureMovementComponent)
	{
		AdventureMovementComponent->RequestHopping();
	}
}

void AAdventurePlayerCharacter::OnPlayerEnterClimbState()
{
	if (AAdventurePlayerController* PlayerController = Cast<AAdventurePlayerController>(GetController()))
	{
		PlayerController->AddClimbMappingContext();
		OnMovementModeChangedDelegate.ExecuteIfBound(ECharacterMovementType::Climb);
	}
}

void AAdventurePlayerCharacter::OnPlayerExitClimbState()
{
	if (AAdventurePlayerController* PlayerController = Cast<AAdventurePlayerController>(GetController()))
	{
		PlayerController->RemoveClimbMappingContext();
		OnMovementModeChangedDelegate.ExecuteIfBound(ECharacterMovementType::Normal);
	}
	if (StaminaCostEffectHandle.IsValid())
	{
		RemoveStaminaCostEffect();
	}
}

void AAdventurePlayerCharacter::Input_CharacterChange_One()
{
	if (CurrentCharacterIndex == 1) return;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, AdventureGameplayTags::Event_CharacterChange_One, FGameplayEventData());
}

void AAdventurePlayerCharacter::Input_CharacterChange_Two()
{
	if (CurrentCharacterIndex == 2) return;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, AdventureGameplayTags::Event_CharacterChange_Two, FGameplayEventData());

}

void AAdventurePlayerCharacter::Input_CharacterChange_Three()
{
	if (CurrentCharacterIndex == 3) return;

	UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, AdventureGameplayTags::Event_CharacterChange_Three, FGameplayEventData());

}

void AAdventurePlayerCharacter::ForceCharacterChange(const int32 IndexToChange)
{
	switch (IndexToChange)
	{
		case 1:
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, AdventureGameplayTags::Event_CharacterChange_One, FGameplayEventData());
			break;
		case 2:
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, AdventureGameplayTags::Event_CharacterChange_Two, FGameplayEventData());
			break;
		case 3:
			UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, AdventureGameplayTags::Event_CharacterChange_Three, FGameplayEventData());
			break;
		default:
			break;
	}
}

void AAdventurePlayerCharacter::ChangeCharacterPartyIndex(const int32 IndexToChange)
{
	CurrentCharacterIndex = IndexToChange;
}

FGameplayTag AAdventurePlayerCharacter::GetOwningCharacterTag()
{
	return CharacterTag;
}


void AAdventurePlayerCharacter::Input_Interaction()
{
	if (OverlappedItems.Num() > 0 && OverlappedItems.Last().IsValid())
	{
		if (AAdventurePlayerState* AdventurePlayerState = Cast<AAdventurePlayerState>(GetPlayerState()))
		{
			FItemSlot ItemSlot;
			ItemSlot.ItemTag = OverlappedItems.Last().Get()->ItemTag;
			ItemSlot.Quantity = OverlappedItems.Last().Get()->Quantity;
			ItemSlot.SlotID = FGuid::NewGuid();
			
			AdventurePlayerState->GetPickupItemInventory()->AddPickupsToAllItems(ItemSlot);
			OverlappedItems.Last()->Destroy();
		}
	}

	for (int32 i = OverlappedItems.Num() - 1; i >= 0; --i)
	{
		if (!OverlappedItems[i].IsValid())
		{
			OverlappedItems.RemoveAt(i);
		}
	}

	OnOverlappedItemChangedDelegate.ExecuteIfBound(OverlappedItems);
	
}

#pragma endregion 
