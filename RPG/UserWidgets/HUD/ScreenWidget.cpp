// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenWidget.h"

#include "HoldingItemSlotSocketWidget.h"
#include "InputActionValue.h"
#include "RPG/UserWidgets/ItemSlotWidget.h"
#include "Components/HorizontalBox.h"

void UScreenWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Cast<UHoldingItemSlotSocketWidget>( HoldingItemBox->GetChildAt( CurrentHoldingItemIndex ) ) ->HandleOnSelect();
}

UHorizontalBox* UScreenWidget::GetHoldingItemBox() const
{
	return HoldingItemBox;
}

UItemPrimaryDataAsset* UScreenWidget::GetHoldingItemAsset() const
{
	return GetHoldingItemSocket()->GetItemAsset();
}

UDraggableSlotSocketWidget* UScreenWidget::GetHoldingItemSocket() const
{
	return Cast<UDraggableSlotSocketWidget>( HoldingItemBox->GetChildAt( CurrentHoldingItemIndex ) );
}

TSharedPtr<FInventoryItem> UScreenWidget::GetHoldingInventorySlot() const
{
	return GetHoldingItemSlot()->GetInventorySlot();
}

UHintBoxWidget* UScreenWidget::GetHintBox() const
{
	return HintBox;
}

UDialogueBox* UScreenWidget::GetDialogueBox() const
{
	return DialogueBox;
}

UItemSlotWidget* UScreenWidget::GetHoldingItemSlot() const
{
	return GetHoldingItemSocket()->GetItemSlot();
}

void UScreenWidget::Scroll( const FInputActionValue& Value)
{
	float MouseWheelValue = Value.Get<float>();
	int32 Offset = 0;
	if( MouseWheelValue > 0.8 ) {
		Offset = 1;
	}
	else if( MouseWheelValue < 0.8 )
	{
		Offset = -1;
	}
	Cast<UHoldingItemSlotSocketWidget>( HoldingItemBox->GetChildAt( CurrentHoldingItemIndex ) ) ->HandleOnUnselect();
	CurrentHoldingItemIndex = ( CurrentHoldingItemIndex + Offset + HoldingItemBox->GetChildrenCount() ) % HoldingItemBox->GetChildrenCount();
	Cast<UHoldingItemSlotSocketWidget>( HoldingItemBox->GetChildAt( CurrentHoldingItemIndex ) ) ->HandleOnSelect();
	
}
