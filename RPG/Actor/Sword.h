// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Sword.generated.h"

UCLASS()
class RPG_API ASword : public AWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ASword();

	virtual void PlayEquipmentMontageNotifyBegin(const FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload) override;

	virtual void PlayUnequipmentMontageNotifyBegin(const FName NotifyName, const FBranchingPointNotifyPayload& BranchingPointPayload) override;
};
