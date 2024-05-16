// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSkeletalMeshComponent.h"
#include "RPG/Interfaces/ItemMeshComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ItemStaticMeshComponent.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UItemStaticMeshComponent : public UStaticMeshComponent, public IItemMeshComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	ETriggerEvent LeftTriggerEvent = ETriggerEvent::Triggered;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	ETriggerEvent RightTriggerEvent = ETriggerEvent::Triggered;
	
protected:
	TWeakObjectPtr<APlayerCharacter> AttachingCharacter;
public:
	virtual APlayerCharacter* GetCharacter() override;

	virtual void AttachToCharacter(APlayerCharacter* Character) override;

	virtual void UpdateEquipmentInputActions() override;

	virtual void LeftUse_Implementation() override;

	virtual void RightUse_Implementation() override;
};
