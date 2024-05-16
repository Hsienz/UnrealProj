﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "Interactable.generated.h"

DECLARE_DYNAMIC_DELEGATE_TwoParams(FInteractionDelegate, AController*, Instigaor, AActor*, Causer );

USTRUCT(BlueprintType,Blueprintable)
struct FInteraction
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	FText InteractionName;

	UPROPERTY(BlueprintReadWrite)
	FInteractionDelegate InteractionDelegate;
};


class UHintWidget;
// This class does not need to be modified.
UINTERFACE()
class UInteractable : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPG_API IInteractable
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:

	virtual TArray<FInteraction>& GetInteractions() = 0;

};
