// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Interface.h"
#include "ItemMeshComponent.generated.h"

class APlayerCharacter;
// This class does not need to be modified.
UINTERFACE()
class UItemMeshComponent : public UInterface
{
	GENERATED_BODY()
};

/**
 * 
 */
class RPG_API IItemMeshComponent
{
	GENERATED_BODY()

	// Add interface functions to this class. This is the class that will be inherited to implement this interface.
public:
	virtual void AttachToCharacter( APlayerCharacter* Character) = 0;

	virtual void UpdateEquipmentInputActions() = 0;

	virtual APlayerCharacter* GetCharacter() = 0;
	
	UFUNCTION( BlueprintNativeEvent, BlueprintCallable )
	void LeftUse();

	UFUNCTION( BlueprintNativeEvent, BlueprintCallable )
	void RightUse();
};
