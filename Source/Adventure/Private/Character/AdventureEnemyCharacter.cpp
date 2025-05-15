// Copyright Choi JinWoo. All Rights Reserved.


#include "Character/AdventureEnemyCharacter.h"

#include "AbilitySystemBlueprintLibrary.h"
#include "AdventureFunctionLibrary.h"
#include "AdventureGameplayTag.h"
#include "DebugHelper.h"
#include "AbilitySystem/AdventureAbilitySystemComponent.h"
#include "AbilitySystem/AdventureAttributeSet.h"
#include "BehaviorTree/BlackboardComponent.h"
#include "Components/BoxComponent.h"
#include "Components/WidgetComponent.h"
#include "Controller/AdventureAIController.h"
#include "DataAsset/StartUpData/DataAsset_StartUpData_Enemy.h"
#include "Engine/AssetManager.h"
#include "GameFramework/CharacterMovementComponent.h" 
#include "Item/Pickups/AdventureInventoryItem.h"
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

	LeftHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("LeftHandCollisionBox");
	LeftHandCollisionBox->SetupAttachment(GetMesh());
	LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	RightHandCollisionBox = CreateDefaultSubobject<UBoxComponent>("RightHandCollisionBox");
	RightHandCollisionBox->SetupAttachment(GetMesh());
	RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	LeftHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
	RightHandCollisionBox->OnComponentBeginOverlap.AddUniqueDynamic(this, &ThisClass::OnBodyCollisionBoxBeginOverlap);
}

void AAdventureEnemyCharacter::OnCharacterDied_Implementation()
{
	Super::OnCharacterDied_Implementation();
	
	AutoPossessAI = EAutoPossessAI::Disabled;
	if (AController* AIController = GetController())
	{
		AIController->UnPossess();
	}
}

void AAdventureEnemyCharacter::SpawnItem()
{
	if (!DropItemClass || DropItemTags.IsEmpty()) return;

	float RandomChance = FMath::FRandRange(1.f, 100.f);
	RandomChance *= EnemyLevel + 10.f;
	
	if (RandomChance < ItemDropChance) return;

	const int32 RandomIndex = FMath::RandRange(0, DropItemTags.Num() - 1);
	const FGameplayTag SelectedItemTag = DropItemTags[RandomIndex];

	FTransform SpawnTransform;
	SpawnTransform.SetLocation(GetActorLocation());

	AAdventureInventoryItem* SpawnedItem = GetWorld()->SpawnActorDeferred<AAdventureInventoryItem>(
		DropItemClass,
		SpawnTransform
	);

	SpawnedItem->ItemTag = SelectedItemTag;
	SpawnedItem->FinishSpawning(SpawnTransform);
	
}


void AAdventureEnemyCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);

	if (BehaviorTree)
	{
		AdventureAIController = Cast<AAdventureAIController>(NewController);
		AdventureAIController->RunBehaviorTree(BehaviorTree);
		AdventureAIController->GetBlackboardComponent()->SetValueAsBool("bIsHitReacting", false);
	}

	InitEnemyStartUpData();
	BindGameplayTagChanged();
	
}

void AAdventureEnemyCharacter::BeginPlay()
{
	Super::BeginPlay();

	Tags.Add("Enemy");
	
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


#if WITH_EDITOR
void AAdventureEnemyCharacter::PostEditChangeChainProperty(struct FPropertyChangedChainEvent& PropertyChangedEvent)
{
	Super::PostEditChangeChainProperty(PropertyChangedEvent);

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, LeftHandCollisionBoxAttachBoneName))
	{
		LeftHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, LeftHandCollisionBoxAttachBoneName);
	}

	if (PropertyChangedEvent.GetMemberPropertyName() == GET_MEMBER_NAME_CHECKED(ThisClass, RightHandCollisionBoxAttachBoneName))
	{
		RightHandCollisionBox->AttachToComponent(GetMesh(), FAttachmentTransformRules::SnapToTargetNotIncludingScale, RightHandCollisionBoxAttachBoneName);
	}
	
}
#endif


void AAdventureEnemyCharacter::OnHitReactTagChanged(const FGameplayTag CallbackTag, int32 NewCount)
{
	Super::OnHitReactTagChanged(CallbackTag, NewCount);
	GetCharacterMovement()->MaxWalkSpeed = bIsHitReacting ? 0.f : MaxWalkSpeed;
	if (AdventureAIController)
	{
		AdventureAIController->GetBlackboardComponent()->SetValueAsBool("IsHitReacting", bIsHitReacting);
	}
}

void AAdventureEnemyCharacter::ToggleWeaponCollision_Implementation(const bool bIsEnable, const EAdventureWeaponType AdventureWeaponType)
{
	Super::ToggleWeaponCollision_Implementation(bIsEnable, AdventureWeaponType);

	if (!bIsEnable)
	{
		LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::NoCollision);
		OverlappedActors.Empty();
		return;
	}
	
	if (AdventureWeaponType == EAdventureWeaponType::LeftHand)
	{
		LeftHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	else if (AdventureWeaponType == EAdventureWeaponType::RightHand)
	{
		RightHandCollisionBox->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	}
	
	
}

void AAdventureEnemyCharacter::BindGameplayTagChanged()
{
	if (!AbilitySystemComponent) return;

	AbilitySystemComponent->RegisterGameplayTagEvent(AdventureGameplayTags::Status_HitReact, EGameplayTagEventType::NewOrRemoved)
		.AddUObject(this, &ThisClass::OnHitReactTagChanged);
}


void AAdventureEnemyCharacter::OnBodyCollisionBoxBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	AAdventureBaseCharacter* AdventureBaseCharacter = Cast<AAdventureBaseCharacter>(OtherActor);
	
	if (OverlappedActors.Contains(OtherActor) || !AdventureBaseCharacter || AdventureBaseCharacter->IsDead_Implementation())
	{
		return;
	}

	OverlappedActors.AddUnique(OtherActor);

	if (UAdventureFunctionLibrary::IsTargetPawnHostile(this, Cast<APawn>(OtherActor)))
	{
		FGameplayEventData Data;
		Data.Instigator = this;
		Data.Target = OtherActor;

		UAbilitySystemBlueprintLibrary::SendGameplayEventToActor(this, AdventureGameplayTags::Event_Hit_Melee, Data);
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
				LoadedData->GrantCharacterLevelEffect(Cast<UAdventureAbilitySystemComponent>(AbilitySystemComponent), EnemyLevel);
				LoadedData->GiveToAbilitySystemComponent(Cast<UAdventureAbilitySystemComponent>(AbilitySystemComponent));
				LoadedData->GrantStartUpGameplayEffect(Cast<UAdventureAbilitySystemComponent>(AbilitySystemComponent));
			}
		})
	);
	
}

