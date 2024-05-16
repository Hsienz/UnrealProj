// Fill out your copyright notice in the Description page of Project Settings.


#include "NeedItemSlotWidget.h"

#include "CraftMenu.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "RPG/Interfaces/HasInventory.h"
#include "Components/TextBlock.h"
#include "RPG/Struct/ItemSlot.h"


void UNeedItemSlotWidget::UpdateTest(UDraggableSlotSocketWidget* Socket, const FInventoryItem& NeedItemSlot)
{
	if( !Cast<IHasInventory>(GetOwningPlayerPawn()))
	{
		UE_LOG( LogTemp, Warning, TEXT("OwningPlayer do not have inventory"));
		return;
	}
	Amount->SetText( FText::FromString(
		FString::FromInt(Cast<IHasInventory>(GetOwningPlayerPawn())->GetInventory()->GetItemAmount( NeedItemSlot.ItemAsset )) +
		"/" +
		FString::FromInt(NeedItemSlot.Stack)) ) ;
}
