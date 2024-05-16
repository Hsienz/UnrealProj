// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "HasMontageComponent.generated.h"

class UMontageComponent;
// This class does not need to be modified.
UINTERFACE()
class UHasMontageComponent : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPG_API IHasMontageComponent
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	UMontageComponent* GetMontageSystem() const;
};
