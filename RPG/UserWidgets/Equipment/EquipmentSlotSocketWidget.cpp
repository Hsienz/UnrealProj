// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentSlotSocketWidget.h"

#include "Blueprint/WidgetBlueprintLibrary.h"
#include "Components/Button.h"
#include "Components/ScaleBox.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "RPG/Character/PlayerCharacter.h"
#include "RPG/Component/Equipment/EquipmentActorComponent.h"
#include "RPG/Component/Equipment/EquipmentManager.h"
#include "RPG/Interfaces/HasInventory.h"
#include "RPG/PrimaryDataAssets/ItemPrimaryDataAsset.h"
#include "RPG/Special/ItemDragAndDropOperation.h"
#include "RPG/Struct/ItemSlot.h"
#include "RPG/UserWidgets/ItemSlotWidget.h"


TArray<TSharedRef<FInventoryItem>> UEquipmentSlotSocketWidget::GetFilteredItems()
{
	TArray<TSharedRef<FInventoryItem>> Res;
	for( FInventoryItem& InventorySlot : Cast<IHasInventory>(GetOwningPlayerPawn())->GetInventory()->GetInventory() )
	{
		if( FilterPass(InventorySlot) )
		{
			Res.Add( MakeShared<FInventoryItem>( InventorySlot ) );
		}	
	}
	return Res;
}

bool UEquipmentSlotSocketWidget::FilterPass(const FInventoryItem& InventorySlot)
{
	if( !InventorySlot.ItemAsset )
	{
		UE_LOG( LogTemp, Error, TEXT("FilterPass: ItemAsset is nullptr"));
		return false;
	}
	if( !InventorySlot.ItemAsset->GetItemClass() )
	{
		UE_LOG( LogTemp, Error, TEXT("FilterPass: ItemClass is nullptr"));
		return false;
	}
	return InventorySlot.ItemAsset->GetItemClass()->IsChildOf(FilterItemClass);
}

TArray<TSharedRef<FInventoryItem>> UEquipmentSlotSocketWidget::GetSortedFilteredItems()
{
	TArray<TSharedRef<FInventoryItem>> Res = GetFilteredItems();
	SortedByName( Res );
	return Res;
}

void UEquipmentSlotSocketWidget::SortedByName(TArray<TSharedRef<FInventoryItem>>& Items)
{
	Items.Sort( [](TSharedRef<FInventoryItem> A, TSharedRef<FInventoryItem> B)
	{
		return A->ItemAsset->GetItemName().ToString() < B->ItemAsset->GetItemName().ToString();
	});
}

const EEquipmentType& UEquipmentSlotSocketWidget::GetBodySocket() const
{
	return BodySocket;
}

void UEquipmentSlotSocketWidget::SetBodySocket(const EEquipmentType& Type)
{
	BodySocket = Type;	
}

void UEquipmentSlotSocketWidget::SetFilterItemClass(UClass* ClassType)
{
	FilterItemClass = ClassType;
}

void UEquipmentSlotSocketWidget::ShowFilteredEquipmentSelectionBox()
{
	UpdateEquipmentSelectionBoxDelegate.ExecuteIfBound( this );
}

void UEquipmentSlotSocketWidget::Equip()
{
	// if taking off equipment, remember to get rid of current equipment by passing nullptr
	UEquipmentActorComponent* EquipmentActorComponent = IHasEquipmentManager::Execute_GetEquipmentManager( GetOwningPlayerPawn() )->GetEquipmentByType(BodySocket);
	if( !EquipmentActorComponent ) return;
	EquipmentActorComponent->SetEquipment(
	GetInventorySlot() ? 
		GetInventorySlot()->ItemAsset->GetItemClass() :
		nullptr
	);
}

bool UEquipmentSlotSocketWidget::NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent,
	UDragDropOperation* InOperation)
{
	UItemDragAndDropOperation* DragOperation = Cast<UItemDragAndDropOperation>( InOperation );
	if( DragOperation )
	{
		if( UItemSlotWidget* SlotWidget = Cast<UItemSlotWidget>( DragOperation->WidgetRef ) )
		{
			if( SlotWidget->GetInventorySlot().IsValid() )
			{
				if( FilterPass( *SlotWidget->GetInventorySlot() ) )
				{
					ExchangeItemSlotInArray( SlotWidget->GetSocket() );
				}
			}
		}
	}
	return false;
}

void UEquipmentSlotSocketWidget::NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent,
	UDragDropOperation*& OutOperation)
{
	Super::NativeOnDragDetected(InGeometry, InMouseEvent, OutOperation);
	/*
	Cast<UItemDragAndDropOperation>( OutOperation )->OnDropSuccessDelete.BindLambda( [&]()
	{
		UEquipmentActorComponent* EquipmentActorComponent = IHasEquipmentManager::Execute_GetEquipmentManager( GetOwningPlayerPawn() )->GetEquipmentByType(BodySocket);
		if( AItemBase* Item = Cast<AItemBase>( EquipmentActorComponent->GetChildActor() ) )
		{
			Item->Unequip();
		}
	} );
	*/
}

FReply UEquipmentSlotSocketWidget::NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent)
{
	Super::NativeOnMouseButtonUp(InGeometry, InMouseEvent);
	ShowFilteredEquipmentSelectionBox();
	return FReply::Handled();
}

void UEquipmentSlotSocketWidget::Refresh()
{
	Super::Refresh();
	Equip();
}
