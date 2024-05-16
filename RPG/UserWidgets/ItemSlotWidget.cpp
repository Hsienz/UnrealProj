// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlotWidget.h"

#include "RPG/ActorComponents/InventorySystem.h"
#include "RPG/PrimaryDataAssets/ItemPrimaryDataAsset.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "RPG/Struct/ItemSlot.h"

void UItemSlotWidget::Update(UDraggableSlotSocketWidget* Socket, TSharedRef<FInventoryItem>& InventorySlot)
{
	SocketRef = Socket;
	SetInventorySlotRef(InventorySlot);
	SyncInventorySlotRefToUI();
}

TSharedPtr<FInventoryItem> UItemSlotWidget::GetInventorySlot() const
{
	return InventorySlotRef;
}

void UItemSlotWidget::SetInventorySlotRef(TSharedRef<FInventoryItem>& InventorySlot)
{
	InventorySlotRef = InventorySlot;
	InventorySlot->InSlotWidget = this;
}

UDraggableSlotSocketWidget* UItemSlotWidget::GetSocket()
{
	return SocketRef.Get();
}

void UItemSlotWidget::SyncInventorySlotRefToUI()
{
	if( InventorySlotRef && InventorySlotRef->ItemAsset )
	{
		ItemIcon->SetBrushFromTexture( InventorySlotRef->ItemAsset->GetItemThumbnail() );
		if( InventorySlotRef->Stack == 1 ) Amount->SetText( FText::FromString(""));
		else Amount->SetText( FText::FromString( FString::FromInt( InventorySlotRef->Stack ) ) );
	}
	else
	{
		ItemIcon->SetBrushFromTexture( nullptr );
		Amount->SetText( FText::FromString(""));
	}
}
