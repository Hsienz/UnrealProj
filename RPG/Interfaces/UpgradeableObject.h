// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "UpgradeableObject.generated.h"

class IUpgradeableAsset;
// This class does not need to be modified.
UINTERFACE()
class UUpgradeableObject : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPG_API IUpgradeableObject
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void Upgrade() = 0;

	virtual IUpgradeableAsset* GetCurrentUpgradeableAsset() = 0;

	IUpgradeableAsset* GetNextUpgradedAsset();
};
