// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "InputTriggers.h"
#include "GameFramework/Actor.h"
#include "RPG/ActorComponents/Montage/MontageComponent.h"
#include "ItemBase.generated.h"

enum class EEquipmentType : uint8;
class UPoseableMeshComponent;
enum class ETriggerEvent : uint8;
class UItemSkeletalMeshComponent;
class APlayerCharacter;
class UItemPrimaryDataAsset;

UENUM()
enum class EMeshType
{
	Static,
	Poseable
};

UCLASS()
class RPG_API AItemBase : public AActor
{
	GENERATED_BODY()


public:
	// Sets default values for this actor's properties
	AItemBase();

	UItemPrimaryDataAsset* GetAsset();
	
protected:
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UStaticMeshComponent* StaticMesh;
	
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UPoseableMeshComponent* PoseableMesh;

	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	EMeshType MeshType = EMeshType::Static;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAnimMontage* EquipMontage;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAnimMontage* UnequipMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bHiddenInGameWhenCreate;

public:
	[[nodiscard]] bool HiddenInGameWhenCreate() const
	{
		return bHiddenInGameWhenCreate;
	}

	[[nodiscard]] UAnimMontage* GetUnequipMontage() const
	{
		return UnequipMontage;
	}

	[[nodiscard]] UAnimMontage* GetEquipMontage() const
	{
		return EquipMontage;
	}

protected:
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	UItemPrimaryDataAsset* Asset;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	ETriggerEvent LeftTriggerEvent = ETriggerEvent::Triggered;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	ETriggerEvent RightTriggerEvent = ETriggerEvent::Triggered;

	TWeakObjectPtr<ACharacter> CharacterRef;

	TWeakObjectPtr<USceneComponent> BodySocketRef;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USceneComponent* RootSceneComponent;

	virtual void PostInitializeComponents() override;

	void InitMeshType();
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void LeftUse();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void RightUse();

	UFUNCTION( BlueprintCallable )
	virtual void Equip(ACharacter* Character, EEquipmentType Type);

	UFUNCTION(BlueprintCallable)
	virtual void Unequip();
	
	UAnimInstance* GetAnimInstance() const;

	ACharacter* GetCharacterRef() const;

	virtual void SetCharacterRef( ACharacter* OwnerCharacter) ;
	
	UMeshComponent* GetMesh();

	void TryPlayEquipMontage();

	UFUNCTION()
	virtual void PlayEquipmentMontageNotifyBegin(const FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload);

	void TryPlayUnequipMontage();

	UFUNCTION()
	virtual void PlayUnequipmentMontageNotifyBegin( const FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload );
};
