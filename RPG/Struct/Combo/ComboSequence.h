// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Combo.h"
#include "ComboSequence.generated.h"

/**
 * 
 */

class UMontageComponent;
struct FCombo;

USTRUCT( Blueprintable )
struct FComboSequence
{
	GENERATED_BODY()
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<FCombo> Combos;
  
	UPROPERTY( EditAnywhere )
	UAnimMontage* DefaultEndMontage;

	TSharedPtr<FCombo> operator[]( int32 Index );
};
