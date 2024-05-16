// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "CraftRecipe.generated.h"


class UItemPrimaryDataAsset;
class UInventorySystem;
struct FInventoryItem;

USTRUCT(BlueprintType)
struct FCraftRecipe
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	TArray<FInventoryItem> NeedItems;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	int32 CraftAmount;
	
	bool IsCraftable( UInventorySystem* InventorySystem ) const ;
	
	bool IsEnoughOnCertainItem( const FInventoryItem* Slot ) const;

	void Craft(UItemPrimaryDataAsset* Item, UInventorySystem* InventorySystem) const;

	int32 GetMaxCraftAmount(UItemPrimaryDataAsset* Item, UInventorySystem* InventorySystem) const;
};
