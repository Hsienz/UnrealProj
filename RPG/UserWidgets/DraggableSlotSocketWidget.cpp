// Fill out your copyright notice in the Description page of Project Settings.


#include "DraggableSlotSocketWidget.h"

#include "InventoryMenu.h"
#include "ItemSlotWidget.h"
#include "Blueprint/SlateBlueprintLibrary.h"
#include "Blueprint/WidgetBlueprintLibrary.h"
#include "RPG/Special/ItemDragAndDropOperation.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "Components/ScaleBox.h"
#include "RPG/Struct/ItemSlot.h"

void UDraggableSlotSocketWidget::NativeConstruct()
{
	Super::NativeConstruct();
}

FReply UDraggableSlotSocketWidget::NativeOnMouseButtonDown(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonDown(InGeometry, InMouseEvent);
	if( !SlotWidgetToUpdate->GetChildrenCount() ) return FReply::Unhandled();
	if( InMouseEvent.GetEffectingButton() == EKeys::LeftMouseButton )
	{
		return HandleLeftMouseClick( InGeometry, InMouseEvent );
	}
	else if( InMouseEvent.GetEffectingButton() == EKeys::RightMouseButton )
	{
		return HandleRightMouseClick( InGeometry, InMouseEvent );
	}
	return FReply::Unhandled();
}

void UDraggableSlotSocketWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	OutOperation = CreateDragDropOperation(InGeometry,InMouseEvent);
}

bool UDraggableSlotSocketWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDrop(InGeometry, InDragDropEvent, InOperation);
	
	UItemDragAndDropOperation* Operation = Cast<UItemDragAndDropOperation>(InOperation);
	UItemSlotWidget* ItemSlotWidget = Cast<UItemSlotWidget>( Operation->WidgetRef );
	ExchangeItemSlotInArray(  ItemSlotWidget->GetSocket() );
	return true;
}

void UDraggableSlotSocketWidget::NativeOnDragCancelled(const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	Super::NativeOnDragCancelled(InDragDropEvent, InOperation);
	SetVisibility(ESlateVisibility::Visible);
}

FReply UDraggableSlotSocketWidget::HandleLeftMouseClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return HandleDrag(InGeometry,InMouseEvent);
}

FReply UDraggableSlotSocketWidget::HandleRightMouseClick(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	return FReply::Handled();
}


FReply UDraggableSlotSocketWidget::HandleDrag(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	bIsDragging = true;
	return UWidgetBlueprintLibrary::DetectDragIfPressed(InMouseEvent, this, EKeys::LeftMouseButton ).NativeReply;
}

FReply UDraggableSlotSocketWidget::HandleDrop(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	bIsDragging = false;
	return FReply::Handled();
}

void UDraggableSlotSocketWidget::UpdateSlotToCurrentArrayElement()
{
	if( !InventoryRef || !InventoryRef.IsValid() || !InventoryRef->IsValidIndex( IndexInInventory ) ) return;
	TSharedRef<FInventoryItem> InventorySlot = MakeShared<FInventoryItem>( ( *InventoryRef )[ IndexInInventory ] );
	if( InventorySlot->ItemAsset == nullptr )
	{
		SlotWidgetToUpdate->ClearChildren();
	}
	else if( SlotWidgetToUpdate->GetChildrenCount() == 0 )
	{
		UItemSlotWidget* NewChild = CreateWidget<UItemSlotWidget>( this, BP_SlotWidget );
		NewChild->Update( this, InventorySlot );
		SlotWidgetToUpdate->AddChild( NewChild );
	}
	else
	{
		Cast<UItemSlotWidget>( SlotWidgetToUpdate->GetChildAt(0) )->Update( this, InventorySlot );
	}
	SocketUpdateDelegate.Broadcast();
}


UItemPrimaryDataAsset* UDraggableSlotSocketWidget::GetItemAsset() const
{
	return GetInventorySlot() ? GetInventorySlot()->ItemAsset : nullptr;
}

void UDraggableSlotSocketWidget::ExchangeItemSlotInArray(UDraggableSlotSocketWidget* OtherSocket)
{
	if( !OtherSocket || !OtherSocket->InventoryRef || !OtherSocket->InventoryRef.IsValid() )
	{
		UE_LOG( LogTemp, Error, TEXT("OtherSocket is error"));
		return;
	}
	// ExchangeItemSlotInArray( OtherSocket->InventoryRef.ToSharedRef(), OtherSocket->IndexInInventory );
	Swap((*InventoryRef)[IndexInInventory], (*OtherSocket->InventoryRef)[OtherSocket->IndexInInventory] );
	Refresh();
	OtherSocket->Refresh();
	OtherSocket->SetVisibility( ESlateVisibility::Visible );
}

void UDraggableSlotSocketWidget::UpdateBelongArray(const FInventorySharedRef NewArray,
                                                   int32 Index)
{
	InventoryRef = NewArray;
	IndexInInventory = Index;
}

void UDraggableSlotSocketWidget::Refresh()
{
	UpdateSlotToCurrentArrayElement();
}

UItemDragAndDropOperation* UDraggableSlotSocketWidget::CreateDragDropOperation(
	const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	UItemDragAndDropOperation* DragOperation = NewObject<UItemDragAndDropOperation>();

	UItemSlotWidget* ItemSlotWidget = Cast<UItemSlotWidget>( SlotWidgetToUpdate->GetChildAt(0));
	// so that this socket would not trigger against mouse, and cause bug, maybe there are better solution
	// set to visibility in NativeOnDragCancel()
	SetVisibility( ESlateVisibility::HitTestInvisible );

	DragOperation->WidgetRef = ItemSlotWidget;
	DragOperation->DragOffset = USlateBlueprintLibrary::AbsoluteToLocal( InGeometry, InMouseEvent.GetScreenSpacePosition() );
	DragOperation->ItemRecord = *GetInventorySlot();

	DragOperation->DefaultDragVisual = ItemSlotWidget;
	DragOperation->Pivot = EDragPivot::MouseDown;

	return DragOperation;
}

TSharedPtr<FInventoryItem> UDraggableSlotSocketWidget::GetInventorySlot() const
{
	if( SlotWidgetToUpdate->GetChildrenCount() == 0 ) return nullptr;
	return Cast<UItemSlotWidget>(SlotWidgetToUpdate->GetChildAt(0) )->GetInventorySlot();
}
