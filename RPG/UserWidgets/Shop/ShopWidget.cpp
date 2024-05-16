// Fill out your copyright notice in the Description page of Project Settings.


#include "ShopWidget.h"

#include "SellingItemWidget.h"
#include "Components/VerticalBox.h"

UVerticalBox* UShopWidget::GetShopItemBox() const
{
	return SellingItemBox;
}

void UShopWidget::RemoveAllSellingItemFromBox()
{
	for( UWidget* ChildWidget: SellingItemBox->GetAllChildren() )
	{
		ChildWidget->RemoveFromParent();
	}
}

void UShopWidget::AddSellingItemToBox(FInventoryItem& SellingItem)
{
	
	USellingItemWidget* NewSellingItemWidget = CreateWidget<USellingItemWidget>( this, BP_SellingItemWidget.Get() );
	NewSellingItemWidget->SetSellingItem( SellingItem );
	SellingItemBox->AddChildToVerticalBox( NewSellingItemWidget );
}
