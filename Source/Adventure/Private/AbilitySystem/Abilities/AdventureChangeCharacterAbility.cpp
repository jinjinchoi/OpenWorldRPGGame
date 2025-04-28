// Copyright Choi JinWoo. All Rights Reserved.


#include "AbilitySystem/Abilities/AdventureChangeCharacterAbility.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "AdventureFunctionLibrary.h"
#include "AbilitySystem/AdventureAbilitySystemComponent.h"
#include "Camera/CameraComponent.h"
#include "Character/AdventurePlayerCharacter.h"
#include "DataAsset/StartUpData/DataAsset_StartUpDataBase.h"
#include "GameFramework/SpringArmComponent.h"
#include "GameManager/ControllableCharacterManager.h"
#include "Player/AdventurePlayerState.h"

void UAdventureChangeCharacterAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}

void UAdventureChangeCharacterAbility::OnCharacterChangeAbilityActivated()
{
	if (CharacterManager) return;

	// 캐릭터 매니저 가져오는 작업 진행
	if (const APlayerController* PC = CurrentActorInfo->PlayerController.Get())
	{
		if (AAdventurePlayerState* AdventurePlayerState = Cast<AAdventurePlayerState>(PC->PlayerState))
		{
			CharacterManager = AdventurePlayerState->GetControllableCharacterManager();
		}
	}
}


void UAdventureChangeCharacterAbility::SpawnNewCharacterAndRemoveOldCharacter(const int32 InCharacterIndex)
{
	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetAvatarActorFromActorInfo()->GetActorLocation());
	SpawnTransform.SetRotation(GetAvatarActorFromActorInfo()->GetActorRotation().Quaternion());

	// 파티 캐릭터 목록에서 캐릭터 인포를 가져옴
	CachedCharacterIndex = InCharacterIndex;
	CachedPartyInfo = *CharacterManager->FindCharacterInfoInPartyCharacterInfo(InCharacterIndex);
	if (!CachedPartyInfo.ClassTag.IsValid())
	{
		// 파티 목록에 캐릭터 정보 없으면 어빌리티 캔슬
		CancelCharacterChangeAbility();
	}
	
	// 현재 사용중인 캐릭터 숨기기
	AAdventurePlayerCharacter* CurrentControlCharacter = GetAdventurePlayerCharacter();
	CurrentControlCharacter->SetActorHiddenInGame(true);
	CurrentControlCharacter->SetActorEnableCollision(false);
	CurrentControlCharacter->DisableInput(nullptr);

	// 현재 사용중인 캐릭터 정보 저장
	UAbilitySystemComponent* ASC = UAbilitySystemBlueprintLibrary::GetAbilitySystemComponent(GetAvatarActorFromActorInfo());
	
	const int32 CurrentCharacterIndex = CurrentControlCharacter->CurrentCharacterIndex;
	const FPartyCharacterInfo CurrentCharacterInfo = UAdventureFunctionLibrary::MakePartyCharacterInfo(CurrentControlCharacter->GetAttributeSet(), ASC, CurrentControlCharacter->GetCharacterClassTag(), false, true, CurrentCharacterIndex);
	CharacterManager->AddOrUpdatePartyCharactersInfo(CurrentCharacterIndex, CurrentCharacterInfo);

	// Soft Object Load 후 작업 시작
	CharacterManager->GetCharacterClassByTag(CachedPartyInfo.ClassTag, [this, SpawnTransform](TSubclassOf<ACharacter> LoadedClass)
	{
		if (LoadedClass)
		{
			
			AAdventurePlayerCharacter* SpawnedCharacter = GetWorld()->SpawnActorDeferred<AAdventurePlayerCharacter>(
				LoadedClass,
				SpawnTransform
			);
			
			// 소환 된 적 있으면 정보가 있기 때문에 복구 진행
			if (!CachedPartyInfo.bIsNotSpawned)
			{
				check(CharacterLoadGameplayEffect);
				
				if (UAdventureAbilitySystemComponent* ASC = SpawnedCharacter->FindComponentByClass<UAdventureAbilitySystemComponent>())
				{
					SpawnedCharacter->bIsFirstLoading = false;
					
					ASC->InitAbilityActorInfo(SpawnedCharacter, SpawnedCharacter);

					SpawnedCharacter->CharacterLoadGameplayEffect = CharacterLoadGameplayEffect;
					SpawnedCharacter->PreviousCharacterInfo = CachedPartyInfo;
					
					// Effect 적용
					// FGameplayEffectContextHandle ContextHandle = ASC->MakeEffectContext();
					// ContextHandle.AddSourceObject(SpawnedCharacter);
					// const FGameplayEffectSpecHandle SpecHandle = ASC->MakeOutgoingSpec(CharacterLoadGameplayEffect, 1.f, ContextHandle);
					// UAdventureFunctionLibrary::InitializeAttributeFromCharacterInfo(CachedPartyInfo, SpecHandle, ASC);
					
					// 어빌리티 부여하고 레벨 설정
					SpawnedCharacter->GetCharacterStartUpData()->GiveToAbilitySystemComponent(ASC);
					ASC->InitializeAbilityFromCharacterInfo(CachedPartyInfo);
				}
			}

			// 소환할 캐릭터 인덱스 설정
			SpawnedCharacter->CurrentCharacterIndex = CachedCharacterIndex;

			// 기존 캐릭터 카메라 정보 저장
			const FRotator OldControlRotation = GetAdventurePlayerCharacter()->GetControlRotation();
			const USpringArmComponent* OldSpringArm = GetAvatarActorFromActorInfo()->FindComponentByClass<USpringArmComponent>();
			const UCameraComponent* OldCamera = GetAvatarActorFromActorInfo()->FindComponentByClass<UCameraComponent>();

			// 바뀔 캐릭터 카메라 정보 저장
			USpringArmComponent* NewSpringArm = SpawnedCharacter->FindComponentByClass<USpringArmComponent>();
			UCameraComponent* NewCamera = SpawnedCharacter->FindComponentByClass<UCameraComponent>();
			
			// 소환 후 Possess
			SpawnedCharacter->FinishSpawning(SpawnTransform);
			CurrentActorInfo->PlayerController->Possess(SpawnedCharacter);

			// 카메라 세팅
			if (AController* NewController = SpawnedCharacter->GetController())
			{
				NewController->SetControlRotation(OldControlRotation);
			}
						
			if (OldSpringArm && NewSpringArm)
			{
				NewSpringArm->TargetArmLength = OldSpringArm->TargetArmLength;
				NewSpringArm->SetRelativeRotation(OldSpringArm->GetRelativeRotation());
				NewSpringArm->SetRelativeLocation(OldSpringArm->GetRelativeLocation());
			}

			if (OldCamera && NewCamera)
			{
				NewCamera->FieldOfView = OldCamera->FieldOfView;
				NewCamera->SetRelativeRotation(OldCamera->GetRelativeRotation());
				NewCamera->SetRelativeLocation(OldCamera->GetRelativeLocation());
			}
						
			if (GetAvatarActorFromActorInfo())
			{
				GetAvatarActorFromActorInfo()->SetLifeSpan(0.1);
			}
		}
	});
	
}


void UAdventureChangeCharacterAbility::CancelCharacterChangeAbility()
{
	CancelAbility(CurrentSpecHandle, CurrentActorInfo, CurrentActivationInfo, true);
}

AAdventurePlayerCharacter* UAdventureChangeCharacterAbility::GetAdventurePlayerCharacter() const
{
	return Cast<AAdventurePlayerCharacter>(GetAvatarActorFromActorInfo());
}
