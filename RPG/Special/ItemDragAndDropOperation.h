// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/DragDropOperation.h"
#include "RPG/Struct/ItemSlot.h"
#include "ItemDragAndDropOperation.generated.h"

/**
 * 
 */
DECLARE_DELEGATE( FOnDropSuccessDelete );

UCLASS()
class RPG_API UItemDragAndDropOperation : public UDragDropOperation
{
	GENERATED_BODY()

public:
	TWeakObjectPtr<UUserWidget> WidgetRef;

	FVector2d DragOffset;

	FInventoryItem ItemRecord;
};
