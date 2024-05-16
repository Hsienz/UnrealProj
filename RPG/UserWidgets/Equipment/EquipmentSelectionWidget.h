// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPG/Struct/ItemSlot.h"
#include "RPG/UserWidgets/DraggableSlotSocketWidget.h"
#include "RPG/UserWidgets/Hint/InteractableHintWidget.h"
#include "EquipmentSelectionWidget.generated.h"

class UDraggableSlotSocketWidget;
struct FInventoryItem;
class AItemBase;
/**
 * 
 */
UCLASS()
class RPG_API UEquipmentSelectionWidget : public UInteractableHintWidget
{
	GENERATED_BODY()

	DECLARE_DELEGATE_OneParam(FEquipmentSwapDelegate, UDraggableSlotSocketWidget* );

	DECLARE_MULTICAST_DELEGATE(FEquipmentSelectionOnClickDelegate);

	TSharedPtr<FInventoryItem> Equipment;
	
	virtual void NativeConstruct() override;
	
public:
	TSharedPtr<FInventoryItem> GetEquipment();

	void SetEquipment( TSharedPtr<FInventoryItem> NewEquipment);

	FEquipmentSwapDelegate EquipmentSwapDelegate;

	FEquipmentSelectionOnClickDelegate EquipmentSelectionOnClickDelegate;
	
	UFUNCTION()
	void InteractionDelegateWrapper();
};
