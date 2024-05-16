﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HasInventory.generated.h"

struct FInventoryItem;
class UInventorySystem;
// This class does not need to be modified.
UINTERFACE()
class UHasInventory : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPG_API IHasInventory
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual UInventorySystem* GetInventory() = 0;
};
