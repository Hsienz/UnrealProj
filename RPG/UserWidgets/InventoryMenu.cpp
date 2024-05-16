// Fill out your copyright notice in the Description page of Project Settings.


#include "InventoryMenu.h"

#include "DraggableSlotSocketWidget.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "Components/UniformGridPanel.h"
#include "RPG/Character/PlayerCharacter.h"

void UInventoryMenu::NativeConstruct()
{
	Super::NativeConstruct();

	if( APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwningPlayerPawn()) )
	{
		InventoryRef = MakeShared<FInventory>( Player->GetInventory()->GetInventory() );
	}
}

void UInventoryMenu::UpdateItemSlotGrid()
{
	if( InventoryRef && InventoryRef.IsValid() )
	{
		for( int32 i = 0 ; i < ItemSlotGrid->GetChildrenCount(); i ++ )
		{
			UDraggableSlotSocketWidget* ItemSlotSocketWidget = Cast<UDraggableSlotSocketWidget>( ItemSlotGrid->GetChildAt(i) );
			ItemSlotSocketWidget->UpdateBelongArray( InventoryRef.ToSharedRef(), i );
			ItemSlotSocketWidget->UpdateSlotToCurrentArrayElement();
		}
	}
}
/*
void UInventoryMenu::SetInventorySystem( UInventorySystem* Inventory )
{
	InventorySystem = Inventory;
}

UInventorySystem* UInventoryMenu::GetInventorySystem() const
{
	return InventorySystem.IsValid() ? InventorySystem.Get() : nullptr;
}
*/
int32 UInventoryMenu::GetItemSlotNum()
{
	return ItemSlotGrid->GetChildrenCount();
}

UUniformGridPanel* UInventoryMenu::GetItemSlotGrid() const
{
	return ItemSlotGrid;
}
