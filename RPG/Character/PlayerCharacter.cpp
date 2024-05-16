// Copyright Epic Games, Inc. All Rights Reserved.

#include "PlayerCharacter.h"

#include "AbilitySystemComponent.h"
#include "EnhancedInputComponent.h"
#include "Animation/AnimInstance.h"
#include "Components/SkeletalMeshComponent.h"
#include "Engine/LocalPlayer.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RPG/Actor/Projectile/Arrow.h"
#include "RPG/ActorComponents/BuildSystem.h"
#include "RPG/ActorComponents/InteractionSystem.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "RPG/ActorComponents/ObjectOptionMenuSystem.h"
#include "RPG/ActorComponents/ScreenComponent.h"
#include "RPG/ActorComponents/Dialogue/DialogueSystem.h"
#include "RPG/ActorComponents/Equipment/EquipmentSystem.h"
#include "RPG/ActorComponents/LimitedValue/Health.h"
#include "RPG/ActorComponents/Montage/MontageComponent.h"
#include "RPG/ActorComponents/UIComponent/UIInventoryComponent.h"
#include "RPG/Component/CollisionTrigger/InteractionHintCollision.h"
#include "RPG/Component/CollisionTrigger/ShowEnemyUICollision.h"
#include "RPG/Component/CollisionTrigger/SpawnFoliageCollision.h"
#include "RPG/GAS/AbilitySystemComponent/EnhancedAbilitySystemComponent.h"
#include "RPG/GAS/GameplayAbility/EnhancedGameplayAbility.h"
#include "RPG/GAS/LimitedValue/HealthAttribute.h"
#include "RPG/PlayerState/GASPlayerState.h"
#include "MotionWarpingComponent.h"
#include "Components/ArrowComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "GameFramework/SpringArmComponent.h"
#include "RPG/ActorComponents/Combo/ComboSystem.h"
#include "RPG/Component/Equipment/EquipmentManager.h"

//////////////////////////////////////////////////////////////////////////
// AMyCharacter

APlayerCharacter::APlayerCharacter()
{
	BuildSystem = CreateDefaultSubobject<UBuildSystem>(TEXT("BuildSystem"));
	ObjectOptionMenuSystem = CreateDefaultSubobject<UObjectOptionMenuSystem>(TEXT("ObjectOptionMenuSystem"));
	InventorySystem = CreateDefaultSubobject<UInventorySystem>(TEXT("InventorySystem"));
	InteractionSystem = CreateDefaultSubobject<UInteractionSystem>(TEXT("InteractionSystem"));
	ScreenHUD = CreateDefaultSubobject<UScreenComponent>(TEXT("ScreenHUD"));
	EquipmentSystem = CreateDefaultSubobject<UEquipmentSystem>(TEXT("EquipmentSystem"));
	DialogueSystem = CreateDefaultSubobject<UDialogueSystem>(TEXT("DialogueSystem"));
	EquipmentManager = CreateDefaultSubobject<UEquipmentManager>(TEXT("EquipmentManager"));
	ComboSystem =CreateDefaultSubobject<UComboSystem>(TEXT("ComboSystem"));
	
	SpawnFoliageCollision = CreateDefaultSubobject<USpawnFoliageCollision>(TEXT("CollisionSpawnFoliageSystem"));
	SpawnFoliageCollision->SetupAttachment( RootComponent );
	
	InteractionHintCollision = CreateDefaultSubobject<UInteractionHintCollision>(TEXT("InteractionHintCollision"));
	InteractionHintCollision->SetupAttachment( RootComponent );

	ShowEnemyUICollision = CreateDefaultSubobject<UShowEnemyUICollision>(TEXT("ShowEnemyUICollision"));
	ShowEnemyUICollision->SetupAttachment(RootComponent);

	UIInventory = CreateDefaultSubobject<UUIInventoryComponent>(TEXT("UIInventory"));
	UIScreen = CreateDefaultSubobject<UUIComponent>(TEXT("UIScreen"));

	MontageComponent = CreateDefaultSubobject<UMontageComponent>(TEXT("MontageComponent"));
	MotionWarpingComponent = CreateDefaultSubobject<UMotionWarpingComponent>(TEXT("MotionWarping"));

	CaptureSpringArm = CreateDefaultSubobject<USpringArmComponent>( TEXT("CaptureSpringArm"));
	CaptureSpringArm->SetupAttachment( RootComponent );
	CaptureSpringArm->bDoCollisionTest = false;
	CaptureSpringArm->SetWorldRotation( FRotator(0,180,0));

	CaptureComponent2D = CreateDefaultSubobject<USceneCaptureComponent2D>(TEXT("CaptureCompoent2D"));
	CaptureComponent2D->SetupAttachment(CaptureSpringArm);
	CaptureComponent2D->ShowOnlyActorComponents( this );


	LeftHandEquipmentActor = EquipmentManager->CreateEquipment( this,GetMesh(), "LeftHandSocket", EEquipmentType::LeftHand );
	RightHandEquipmentActor = EquipmentManager->CreateEquipment( this, GetMesh(), "RightHandSocket", EEquipmentType::RightHand );
}

float APlayerCharacter::GetReachDistance()
{
	return ReachDistance;
}

void APlayerCharacter::BeginPlay()
{
	// Call the base class  
	Super::BeginPlay();
}

void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	EquipmentSystem->SetupPlayerInputComponent( PlayerInputComponent );
	InteractionSystem->SetupPlayerInputComponent(PlayerInputComponent);
	DialogueSystem->SetupPlayerInputComponent(PlayerInputComponent);
	InventorySystem->SetupPlayerInputComponent(PlayerInputComponent);

	BindingAbilitiesInput();
}

void APlayerCharacter::BindingAbilitiesInput()
{
	if( !Cast<UEnhancedInputComponent>( InputComponent ) || !GetPlayerState() || !AbilitySystemComponentPtr.IsValid() || AbilitySystemComponentPtr->bInputBindingInitialized ) return;
	Cast<AGASPlayerState>( GetPlayerState() )->GetAbilitySystemComponent()->BindAbilityActivationToInputComponent( InputComponent,
		FGameplayAbilityInputBinds(
			FString("ConfirmTarget"),
			FString("CancelTarget"),
			FTopLevelAssetPath(FName("/Script/RPG"), FName("EGameplayAbilityBindingType") ),
			static_cast<int32>( EGameplayAbilityBindingType::ConfirmTarget ),
			static_cast<int32>(EGameplayAbilityBindingType::CancelTarget)
		)
	);
	AbilitySystemComponentPtr->bInputBindingInitialized = true;
}

void APlayerCharacter::OnRep_PlayerState()
{
	Super::OnRep_PlayerState();
	AGASPlayerState* PS = Cast<AGASPlayerState>(GetPlayerState());
	if( PS ) {
		AbilitySystemComponentPtr = PS->AbilitySystemComponent;
		AbilitySystemComponentPtr->InitAbilityActorInfo( PS, this );
		BindingAbilitiesInput();
	}
}


void APlayerCharacter::PossessedBy(AController* NewController)
{
	Super::PossessedBy(NewController);
	AGASPlayerState* PS = Cast<AGASPlayerState>(GetPlayerState());
	if( PS ) {
		AbilitySystemComponentPtr = PS->AbilitySystemComponent;
		AbilitySystemComponentPtr->InitAbilityActorInfo( PS, this );
		GiveDefaultAbilities();
		ApplyDefaultEffects();
	}
}

//////////////////////////////////////////////////////////////////////////// Input

UInventorySystem* APlayerCharacter::GetInventory()
{
	return InventorySystem;
}

ULimitedValue* APlayerCharacter::GetStatus(EStatusType Type) const 
{
	switch (Type)
	{
	case EStatusType::Health:
		// return Health;
		break;
	case EStatusType::Hydration:
		// return Hydration;
		break;
	}
	return nullptr;
}

UScreenComponent* APlayerCharacter::GetScreenHUD() const
{
	return ScreenHUD;
}

UEquipmentSystem* APlayerCharacter::GetEquipmentSystem() const
{
	return EquipmentSystem;
}

UMotionWarpingComponent* APlayerCharacter::GetMotionWarpingComponent_Implementation() const
{
	return MotionWarpingComponent;
}

UCameraComponent* APlayerCharacter::GetCamera() const
{
	return GetFollowCamera();
}


UUIInventoryComponent* APlayerCharacter::GetUIInventory() const
{
	return UIInventory;
}

UUIComponent* APlayerCharacter::GetUIScreen() const
{
	return UIScreen;
}

UMontageComponent* APlayerCharacter::GetMontageSystem_Implementation() const
{
	return MontageComponent;
}

USceneCaptureComponent2D* APlayerCharacter::GetEquipmentCaptureComponent() const
{
	return CaptureComponent2D;
}

UComboSystem* APlayerCharacter::GetComboSystem_Implementation() const
{
	return ComboSystem;
}

UEquipmentManager* APlayerCharacter::GetEquipmentManager_Implementation() const
{
	return EquipmentManager;
}

UHealthAttribute* APlayerCharacter::GetHealthAttribute_Implementation() const
{
	return Cast<AGASPlayerState>(GetPlayerState())->HealthAttribute;
}

float APlayerCharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	Cast<AGASPlayerState>( GetPlayerState() )->HealthAttribute->SubHealth(DamageAmount);
	return DamageAmount;
}
