// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SlotSocketWidget.h"
#include "Blueprint/UserWidget.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "DraggableSlotSocketWidget.generated.h"

class UItemDragAndDropOperation;
class UInventoryMenu;
class UItemPrimaryDataAsset;
class UContentWidget;
class UItemSlotWidget;
class UScaleBox;
class UInventoryItemSlotWidget;
struct FInventoryItem;
class UBorder;
/**
 * 
 */

DECLARE_MULTICAST_DELEGATE( FSocketUpdateDelegate );

using FInventorySharedPtr = TSharedPtr<FInventory>;
using FInventorySharedRef = TSharedRef<FInventory>;

UCLASS()
class RPG_API UDraggableSlotSocketWidget : public USlotSocketWidget
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TSubclassOf<UItemSlotWidget> BP_SlotWidget;

	FInventorySharedPtr InventoryRef;
	
	int32 IndexInInventory = -1;
protected:
	
	virtual void NativeConstruct() override;

	virtual FReply NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual FReply HandleLeftMouseClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	virtual FReply HandleRightMouseClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	virtual FReply HandleDrag(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);

	virtual FReply HandleDrop(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	
	bool bIsDragging;

	FVector2d DragStartLocation;


	UItemDragAndDropOperation* CreateDragDropOperation(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent);
	
public:
	FSocketUpdateDelegate SocketUpdateDelegate;

	TSharedPtr<FInventoryItem> GetInventorySlot() const;

	virtual void UpdateSlotToCurrentArrayElement();
	
	UItemPrimaryDataAsset* GetItemAsset() const;

	virtual void ExchangeItemSlotInArray( UDraggableSlotSocketWidget* OtherSocket );
	
	void UpdateBelongArray(const FInventorySharedRef NewArray, int32 Index);

	virtual void Refresh();
};

