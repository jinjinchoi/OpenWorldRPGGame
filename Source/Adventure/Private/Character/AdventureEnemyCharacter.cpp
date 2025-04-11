// Copyright Choi JinWoo. All Rights Reserved.


#include "Character/AdventureEnemyCharacter.h"

#include "DebugHelper.h"
#include "AbilitySystem/AdventureAbilitySystemComponent.h"
#include "AbilitySystem/AdventureAttributeSet.h"
#include "Components/CapsuleComponent.h"
#include "Components/WidgetComponent.h"
#include "DataAsset/StartUpData/DataAsset_StartUpDataBase.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "UI/Widget/AdventureUserWidget.h"

AAdventureEnemyCharacter::AAdventureEnemyCharacter(const FObjectInitializer& ObjectInitializer)
	: Super(ObjectInitializer)
{
	AutoPossessAI = EAutoPossessAI::PlacedInWorldOrSpawned;

	bUseControllerRotationPitch = false;
	bUseControllerRotationYaw = false;
	bUseControllerRotationRoll = false;

	GetCharacterMovement()->bUseControllerDesiredRotation = false;
	GetCharacterMovement()->bOrientRotationToMovement = true;
	GetCharacterMovement()->RotationRate = FRotator(0.0f, 180.f, 0.f);
	GetCharacterMovement()->MaxWalkSpeed = MaxWalkSpeed;
	GetCharacterMovement()->BrakingDecelerationWalking = 1000.f;

	EnemyHealthBar = CreateDefaultSubobject<UWidgetComponent>("HealthBar");
	EnemyHealthBar->SetupAttachment(GetRootComponent());
	
}

void AAdventureEnemyCharacter::OnEnemyDied_Implementation()
{
	AutoPossessAI = EAutoPossessAI::Disabled;
	if (AController* AIController = GetController())
	{
		AIController->UnPossess();
	}
	GetCapsuleComponent()->SetCollisionEnabled(ECollisionEnabled::NoCollision);
	GetMesh()->bPauseAnims = true;
}

void AAdventureEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	InitEnemyStartUpData();

	
}

void AAdventureEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (UAdventureUserWidget* AdventureUserWidget = Cast<UAdventureUserWidget>(EnemyHealthBar->GetUserWidgetObject()))
	{
		AdventureUserWidget->SetWidgetController(this);
	}

	if (const UAdventureAttributeSet* AdventureAttributeSet = CastChecked<UAdventureAttributeSet>(AttributeSet))
	{
		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AdventureAttributeSet->GetCurrentHealthAttribute()).
		AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnHealthChangeDelegate.Broadcast(Data.NewValue);
		});

		AbilitySystemComponent->GetGameplayAttributeValueChangeDelegate(AdventureAttributeSet->GetMaxHealthAttribute()).
		AddLambda([this](const FOnAttributeChangeData& Data)
		{
			OnMaxHealthChangeDelegate.Broadcast(Data.NewValue);
		});
		
	}
	
}


void AAdventureEnemyCharacter::InitEnemyStartUpData() const
{
	if (CharacterStartUpData.IsNull())
	{
		DebugHelper::Print(FString::Printf(TEXT("You need to assign startup data to %s"), *GetName()), FColor::Yellow);
		return;
	}

	UAssetManager::GetStreamableManager().RequestAsyncLoad(
		CharacterStartUpData.ToSoftObjectPath(),
		FStreamableDelegate::CreateLambda([this]
		{
			if (UDataAsset_StartUpDataBase* LoadedData = CharacterStartUpData.Get())
			{
				LoadedData->GiveToAbilitySystemComponent(Cast<UAdventureAbilitySystemComponent>(AbilitySystemComponent));
			}
		})
	);
	
}
