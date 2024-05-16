// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentWidget.h"

#include "EquipmentSelectionBoxWidget.h"
#include "EquipmentSelectionWidget.h"
#include "EquipmentSlotSocketWidget.h"
#include "RPG/Actor/Bow.h"
#include "RPG/Character/PlayerCharacter.h"
#include "RPG/Component/Equipment/EquipmentManager.h"
#include "RPG/PrimaryDataAssets/ItemPrimaryDataAsset.h"
#include "RPG/UserWidgets/Hint/InteractableHintBoxWidget.h"
#include "RPG/UserWidgets/Hint/InteractableHintWidget.h"

bool UEquipmentWidget::Initialize()
{
	if( !Super::Initialize() ) return false;
	if( LeftHandSocketWidget )
	{
		LeftHandSocketWidget->SetBodySocket( EEquipmentType::LeftHand );
		LeftHandSocketWidget->UpdateEquipmentSelectionBoxDelegate.BindUObject(this,&UEquipmentWidget::UpdateEquipmentSelectionBox);
	}

	if( RightHandSocketWidget )
	{
		RightHandSocketWidget->SetBodySocket( EEquipmentType::RightHand );
		RightHandSocketWidget->UpdateEquipmentSelectionBoxDelegate.BindUObject(this,&UEquipmentWidget::UpdateEquipmentSelectionBox);
	}
	return true;
}

void UEquipmentWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if( UEquipmentManager* EquipmentManager = IHasEquipmentManager::Execute_GetEquipmentManager( GetOwningPlayerPawn() ) )
	{
		if( UInventorySystem* InventorySystem = EquipmentManager->GetInventory() )
		{
			FInventorySharedRef InventorySharedRef = MakeShared<FInventory>( InventorySystem->GetInventory() );
			if( LeftHandSocketWidget ) LeftHandSocketWidget->UpdateBelongArray( InventorySharedRef, 0);
			if( RightHandSocketWidget ) RightHandSocketWidget->UpdateBelongArray( InventorySharedRef, 1);
		}
	}
}

void UEquipmentWidget::HandleOnEquipmentSelectionWidgetClick()
{
	EquipmentBox->SetVisibility(ESlateVisibility::Hidden);
}

void UEquipmentWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	// UE_LOG( LogTemp, Log, TEXT("%p"), Cast<APlayerCharacter>(GetOwningPlayerPawn())->GetEquipmentManager() );
}

void UEquipmentWidget::UpdateEquipmentSelectionBox(UEquipmentSlotSocketWidget* SocketWidget)
{
	EquipmentBox->ClearChildren();
	EquipmentBox->SetVisibility( ESlateVisibility::Visible );
	for( TSharedRef<FInventoryItem> Equipment: SocketWidget->GetSortedFilteredItems() )
	{
		UEquipmentSelectionWidget* HintWidget = Cast<UEquipmentSelectionWidget>( EquipmentBox->Add() );
		HintWidget->SetHintIcon( Equipment->ItemAsset->GetItemThumbnail() );
		HintWidget->SetHintText( Equipment->ItemAsset->GetItemText() );
		HintWidget->SetEquipment( Equipment );
		HintWidget->EquipmentSwapDelegate.BindUObject( SocketWidget, &UEquipmentSlotSocketWidget::ExchangeItemSlotInArray );
		HintWidget->EquipmentSelectionOnClickDelegate.AddUObject( this, &UEquipmentWidget::HandleOnEquipmentSelectionWidgetClick );
		UE_LOG(LogTemp, Log, TEXT("%d"), static_cast<int32>( HintWidget->GetVisibility() ) );
	}
}
