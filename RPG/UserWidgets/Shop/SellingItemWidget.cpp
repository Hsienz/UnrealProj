// Fill out your copyright notice in the Description page of Project Settings.


#include "SellingItemWidget.h"

#include "Components/Image.h"
#include "Components/TextBlock.h"
#include "RPG/PrimaryDataAssets/ItemPrimaryDataAsset.h"
#include "RPG/Struct/ItemSlot.h"

void USellingItemWidget::SetSellingItem(FInventoryItem& SellingItemSlot)
{
	SellingItem = &SellingItemSlot;
	ItemNameText->SetText( SellingItem->ItemAsset->GetItemText() );
	ItemIcon->SetBrushFromTexture( SellingItem->ItemAsset->GetItemThumbnail() );
	RemainingAmount->SetText( FText::FromString( FString::FromInt( SellingItem->Stack )));
}

FInventoryItem* USellingItemWidget::GetSellingItem() const
{
	return SellingItem;
}
