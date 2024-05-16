// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftItemSelectionWidget.h"

#include "..\..\Character\PlayerCharacter.h"
#include "RPG/Interfaces/HasInventory.h"
#include "Components/Button.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"

void UCraftItemSelectionWidget::UpdateAsset( UItemPrimaryDataAsset* NewAsset)
{
	Asset = NewAsset;
	if( !Asset ) return;
	ItemName->SetText( Asset->GetItemText() );
	ItemIcon->SetBrushFromTexture( Asset->GetItemThumbnail() );
	if( Cast<APlayerCharacter>( GetOwningPlayerPawn() ) )
	{
		UE_LOG( LogTemp, Log, TEXT("AMyCharacter"));
	}
	if( Cast<IHasInventory>( GetOwningPlayerPawn()) )
	{
		UE_LOG( LogTemp, Log, TEXT("HasInventory"));
	}
	
	if( IHasInventory* HasInventory =  Cast<IHasInventory>(GetOwningPlayerPawn() ) )
	{
		if( Asset->IsCraftable( HasInventory->GetInventory() ) )
		{
			bIsCraftable = true;
		}
		else
		{
			Button->SetIsEnabled( false );
			bIsCraftable = false;
		}
	}
}

bool UCraftItemSelectionWidget::IsCraftable() const
{
	return bIsCraftable;
}

UItemPrimaryDataAsset* UCraftItemSelectionWidget::GetAsset() const 
{
	return Asset;
}

bool UCraftItemSelectionWidget::operator<(const UCraftItemSelectionWidget& Other) const
{
	if( IsCraftable() == Other.IsCraftable() ) return Asset->GetItemName().ToString() < Other.GetAsset()->GetItemName().ToString();
	return IsCraftable() > Other.IsCraftable();
}

void UCraftItemSelectionWidget::OnClick()
{
	OnButtonClick.ExecuteIfBound( Asset );
}

void UCraftItemSelectionWidget::NativeConstruct()
{
	Super::NativeConstruct();
	UpdateAsset( Asset );
	
	Button->OnClicked.AddDynamic( this,  &UCraftItemSelectionWidget::OnClick );
}
