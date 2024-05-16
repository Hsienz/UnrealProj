// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "RPG/ActorComponents/BuildSystem.h"
#include "RPG/Interfaces/HasInventory.h"
#include "Logging/LogMacros.h"
#include "RPG/RPGCharacter.h"
#include "RPG/Interfaces/Damageable.h"
#include "RPG/Interfaces/DamageableActor.h"
#include "RPG/Interfaces/DamageableGasActor.h"
#include "RPG/Interfaces/HasComboSystem.h"
#include "RPG/Interfaces/HasEquipmentManager.h"
#include "RPG/Interfaces/HasMontageComponent.h"
#include "RPG/Interfaces/HasMotionWrappingComponent.h"
#include "PlayerCharacter.generated.h"

class UEquipmentActorComponent;
class UEquipmentManager;
class UMontageComponent;
class UGameplayEffect;
class UGameplayAbility;
class UHealthAttribute;
class UAbilitySystemComponent;
class UDialogueSystem;
class AArrow;
class UUIComponent;
class UUIInventoryComponent;
class UShowEnemyUICollision;
class USphereComponent;
class UEquipmentSystem;
class UInteractionHintCollision;
class UScreenComponent;
class UScreenWidget;
class UWidget;
class ULimitedValue;
class UHealth;
class USpawnFoliageCollision;
class UInteractionSystem;
class UInventorySystem;
class UObjectOptionMenuSystem;
class UEnhancedInputLocalPlayerSubsystem;
class UInputComponent;
class USkeletalMeshComponent;
class UCameraComponent;
class UInputAction;
class UInputMappingContext;
class UMotionWarpingComponent;
struct FInputActionValue;

UENUM()
enum class EStatusType
{
	Health,
	Hydration,
};



UCLASS(config=Game)
class APlayerCharacter : public ARPGCharacter,
public IHasInventory,
public IHasMontageComponent,
public IHasComboSystem,
public IHasMotionWrappingComponent,
public IHasEquipmentManager,
public IDamageable,
public IDamageableGasActor
{
	GENERATED_BODY()
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UUIInventoryComponent* UIInventory;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UUIComponent* UIScreen;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=ActorComponent, meta=(AllowPrivateAccess ="true"))
	UBuildSystem* BuildSystem;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category=ActorComponent, meta=(AllowPrivateAccess ="true"))
	UObjectOptionMenuSystem* ObjectOptionMenuSystem;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=ActorComponent, meta=(AllowPrivateAccess))
	UInventorySystem* InventorySystem;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,Category=ActorComponent, meta=(AllowPrivateAccess))
	UInteractionSystem* InteractionSystem;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,Category=ActorComponent, meta=(AllowPrivateAccess))
	USpawnFoliageCollision* SpawnFoliageCollision;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UInteractionHintCollision* InteractionHintCollision;
	
	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	float ReachDistance = 1000;

	UPROPERTY(VisibleAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	UScreenComponent* ScreenHUD;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UEquipmentSystem* EquipmentSystem;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UDialogueSystem* DialogueSystem;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UComboSystem* ComboSystem;

	float VerticalVelocity;

	float HorizontalVelocity;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UShowEnemyUICollision* ShowEnemyUICollision;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UMontageComponent* MontageComponent;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UMotionWarpingComponent* MotionWarpingComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	USpringArmComponent* CaptureSpringArm;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	USceneCaptureComponent2D* CaptureComponent2D;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UEquipmentManager* EquipmentManager;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UEquipmentActorComponent* LeftHandEquipmentActor;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UEquipmentActorComponent* RightHandEquipmentActor;
public:
	APlayerCharacter();

	float GetReachDistance();
protected:
	virtual void BeginPlay();

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	void BindingAbilitiesInput();
public:

	virtual void OnRep_PlayerState() override;

	virtual void PossessedBy(AController* NewController) override;
	
	UInventorySystem* GetInventory() override;

	ULimitedValue* GetStatus( EStatusType Type ) const ;

	UScreenComponent* GetScreenHUD() const;

	UEquipmentSystem* GetEquipmentSystem() const;

	UMotionWarpingComponent* GetMotionWarpingComponent_Implementation() const override;

	UCameraComponent* GetCamera() const;

	UUIInventoryComponent* GetUIInventory() const;

	UUIComponent* GetUIScreen() const;

	virtual UMontageComponent* GetMontageSystem_Implementation() const override;

	USceneCaptureComponent2D* GetEquipmentCaptureComponent() const;

	virtual UComboSystem* GetComboSystem_Implementation() const override;
	
	virtual UEquipmentManager* GetEquipmentManager_Implementation() const override;
	
	virtual UHealthAttribute* GetHealthAttribute_Implementation() const override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;
};

