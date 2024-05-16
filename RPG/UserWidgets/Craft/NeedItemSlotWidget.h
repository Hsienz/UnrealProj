// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPG/UserWidgets/ItemSlotWidget.h"
#include "NeedItemSlotWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UNeedItemSlotWidget : public UItemSlotWidget
{
	GENERATED_BODY()

public:
	virtual void UpdateTest(UDraggableSlotSocketWidget* Socket, const FInventoryItem& Item);
	
};
