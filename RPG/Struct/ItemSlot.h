// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemSlot.generated.h"

class UItemSlotWidget;
class UItemPrimaryDataAsset;
/**
 * 
 */
USTRUCT(BlueprintType,Blueprintable)
struct FInventoryItem
{
	GENERATED_BODY()

	FInventoryItem();

	FInventoryItem( UItemPrimaryDataAsset* ItemAsset, int32 Stack );
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	UItemPrimaryDataAsset* ItemAsset = nullptr;

	UPROPERTY( EditAnywhere, BlueprintReadWrite )
	int32 Stack = 0;

	TWeakObjectPtr<UItemSlotWidget> InSlotWidget;

};
