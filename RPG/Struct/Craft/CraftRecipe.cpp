// Fill out your copyright notice in the Description page of Project Settings.


#include "CraftRecipe.h"

#include "RPG/ActorComponents/InventorySystem.h"
#include "RPG/PrimaryDataAssets/ItemPrimaryDataAsset.h"
#include "RPG/Struct/ItemSlot.h"


bool FCraftRecipe::IsCraftable(UInventorySystem* InventorySystem) const 
{
	for( const FInventoryItem& NeedItem : NeedItems )
	{
		if( InventorySystem->GetItemAmount( NeedItem.ItemAsset ) < NeedItem.Stack )
		{
			return false;
		}
	}
	return true;
}

bool FCraftRecipe::IsEnoughOnCertainItem( const FInventoryItem* Slot) const 
{
	for( const FInventoryItem& NeedItem : NeedItems )
	{
		if(Slot->ItemAsset == NeedItem.ItemAsset )
		{
			return Slot->Stack >= NeedItem.Stack;
		}
	}
	return true;
}

void FCraftRecipe::Craft(UItemPrimaryDataAsset* Item, UInventorySystem* InventorySystem) const
{
	if( IsCraftable( InventorySystem ) )
	{
		InventorySystem->AddItem( Item, CraftAmount );
	}
}

int32 FCraftRecipe::GetMaxCraftAmount(UItemPrimaryDataAsset* Item, UInventorySystem* InventorySystem) const
{
	int32 Res = Item->GetMaxStack();
	for( const FInventoryItem& x : NeedItems )
	{
		Res = FMath::Min( Res, InventorySystem->GetItemAmount( x.ItemAsset ) / x.Stack );
	}
	return Res;
}
