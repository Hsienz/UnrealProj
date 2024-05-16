// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentSelectionWidget.h"

#include "EquipmentWidget.h"
#include "Components/Button.h"
#include "RPG/Actor/ItemBase.h"
#include "RPG/UserWidgets/ItemSlotWidget.h"

void UEquipmentSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	Button->OnClicked.AddDynamic( this, &UEquipmentSelectionWidget::InteractionDelegateWrapper );
}

TSharedPtr<FInventoryItem> UEquipmentSelectionWidget::GetEquipment()
{
	return Equipment;
}

void UEquipmentSelectionWidget::SetEquipment( TSharedPtr<FInventoryItem> NewEquipment)
{
	Equipment = NewEquipment;
}

void UEquipmentSelectionWidget::InteractionDelegateWrapper( )
{
	UE_LOG( LogTemp, Log, TEXT("asd"));
	EquipmentSwapDelegate.ExecuteIfBound( Equipment->InSlotWidget->GetSocket() );
	EquipmentSelectionOnClickDelegate.Broadcast();
}
