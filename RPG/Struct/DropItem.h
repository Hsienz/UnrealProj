// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "DropItem.generated.h"


struct FInventoryItem;
class UItemPrimaryDataAsset;

UENUM()
enum ECollectMethod
{
	Fixed,					// would get fixed amount, MinAmount item
	Dynamic,				// start from MinAmount, there is Possibility to get one more, until running out luck or meeting MaxAmount
	Random,					// get random Amount between MinAmount and MaxAmount
};

USTRUCT(BlueprintType)
struct FDropItem
{
	GENERATED_BODY()

public:

	UPROPERTY(BlueprintReadWrite, EditAnywhere )
	UItemPrimaryDataAsset* Item;

	UPROPERTY(BlueprintReadWrite, EditAnywhere )
	int32 MinAmount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere)
	int32 MaxAmount;

	UPROPERTY(BlueprintReadWrite, EditAnywhere )
	float Possibility;

	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	float FirstUnderPossibility = 1; // if you miss this possibility, you get nothing
	
	UPROPERTY( BlueprintReadWrite, EditAnywhere )
	TEnumAsByte<ECollectMethod> CollectMethod;

	int32 GetRandomAmount() const;

	FInventoryItem GetSlotWidthRandomAmount() const;
};
