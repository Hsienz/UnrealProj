// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftMenu.h"

#include "CraftItemSelectionWidget.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "Components/Button.h"
#include "Components/HorizontalBox.h"
#include "Components/HorizontalBoxSlot.h"
#include "Components/Image.h"
#include "Components/ScrollBox.h"
#include "Components/ScrollBoxSlot.h"
#include "Components/Slider.h"
#include "Components/TextBlock.h"
#include "RPG/Interfaces/HasInventory.h"
#include "RPG/Struct/ItemSlot.h"

void UCraftMenu::Craft()
{
	if( Asset.IsValid() )
	{
		Asset->GetCraftRecipe().Craft(Asset.Get(), Cast<IHasInventory>(GetOwningPlayerPawn())->GetInventory());
	}
}

FText UCraftMenu::SliderValueSyncToText()
{
	return FText::FromString( FString::FromInt( FMath::RoundToInt32( CraftAmountSliderBar->GetValue() ) ) );
}

TArray<UCraftItemSelectionWidget*> UCraftMenu::PrepareCraftItemSelectionWidget()
{
	TArray<UCraftItemSelectionWidget*> Res;
	for( UItemPrimaryDataAsset* Item: CraftableItems )
	{
		UCraftItemSelectionWidget* Widget = CreateWidget<UCraftItemSelectionWidget>( this, CraftItemSelectionWidget );
		Widget->UpdateAsset( Item );
		Widget->OnButtonClick.BindUObject( this, &UCraftMenu::UpdateAsset );
		Res.Add( Widget );
	}
	Res.Sort();
	return Res;
}

void UCraftMenu::NativeConstruct()
{
	Super::NativeConstruct();
}

bool UCraftMenu::Initialize()
{
	if( !Super::Initialize() ) return false;
	CraftAmountText->TextDelegate.BindUFunction( this, "SliderValueSyncToText" );
	CraftButton->OnClicked.AddDynamic( this, &UCraftMenu::Craft );
	UpdateAsset( Asset.Get());

	TArray<UCraftItemSelectionWidget*> Widgets = PrepareCraftItemSelectionWidget();
	for( UCraftItemSelectionWidget* x : Widgets )
	{
		UScrollBoxSlot* ScrollBoxSlot = Cast<UScrollBoxSlot>( CraftableItemBox->AddChild( x ) );
		ScrollBoxSlot->SetPadding( 10 );
		ScrollBoxSlot->SetHorizontalAlignment( HAlign_Center );
	}

	return true;
}

void UCraftMenu::UpdateAsset(UItemPrimaryDataAsset* NewAsset)
{
	
	NeedItemBox->ClearChildren();
	Asset = NewAsset;
	if( Asset.IsValid() )
	{
		CraftTargetPreview->SetBrushFromTexture( Asset->GetItemThumbnail() );
		CraftAmountSliderBar->SetMaxValue( 99 ); //Asset->GetMaxCraftNum( Cast<AMyCharacter>( GetOwningPlayerPawn() )->GetInventory() ) );
		CraftAmountSliderBar->SetValue( 1 );
		CraftTargetPreview->SetOpacity(1);
		for( const FInventoryItem& NeedItemSlot : Asset->GetCraftRecipe().NeedItems )
		{
			UNeedItemSlotWidget* ItemSlotWidget = CreateWidget<UNeedItemSlotWidget>( this, NeedItemSlotWidget.Get() );
			ItemSlotWidget->UpdateTest( nullptr, NeedItemSlot );
			UHorizontalBoxSlot* HorizontalBoxSlot = NeedItemBox->AddChildToHorizontalBox( ItemSlotWidget );
			HorizontalBoxSlot->SetPadding( 5 );
			HorizontalBoxSlot->SetVerticalAlignment( VAlign_Center );
		}
	}
	else
	{
		CraftTargetPreview->SetOpacity( 0 );
	}
}
