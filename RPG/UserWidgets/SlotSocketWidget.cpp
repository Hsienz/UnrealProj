// Fill out your copyright notice in the Description page of Project Settings.


#include "SlotSocketWidget.h"
#include "Components/ContentWidget.h"
#include "Components/ScaleBox.h"
#include "ItemSlotWidget.h"

UContentWidget* USlotSocketWidget::GetContentWidget() const 
{
	return Cast<UContentWidget>( SlotWidgetToUpdate );
}

UItemSlotWidget* USlotSocketWidget::GetItemSlot() const
{
	return SlotWidgetToUpdate->GetChildrenCount() ? Cast<UItemSlotWidget>(SlotWidgetToUpdate->GetChildAt(0)) : nullptr;
}
