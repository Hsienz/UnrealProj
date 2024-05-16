// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combo.generated.h"

USTRUCT( Blueprintable )
struct FCombo
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAnimMontage* AttackMontage;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAnimMontage* EndMontage;
	
};