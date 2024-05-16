// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemPrimaryDataAsset.h"

const FText& UItemPrimaryDataAsset::GetItemText() const
{
	return ItemText;
}

const FName& UItemPrimaryDataAsset::GetItemName() const
{
	return ItemName;
}

const FText& UItemPrimaryDataAsset::GetItemDescription() const
{
	return ItemDescription;
}

UTexture2D* UItemPrimaryDataAsset::GetItemThumbnail() const
{
	return ItemThumbnail;
}

UStaticMesh* UItemPrimaryDataAsset::GetItemStaticMesh() const
{
	return ItemMesh;
}

USkeletalMesh* UItemPrimaryDataAsset::GetItemSkeletalMesh() const
{
	return ItemSkeletalMesh;
}

TObjectPtr<UClass> UItemPrimaryDataAsset::GetItemClass() const
{
	return ItemClass;
}

int32 UItemPrimaryDataAsset::GetMaxStack() const
{
	return MaxStack;
}

const FCraftRecipe& UItemPrimaryDataAsset::GetCraftRecipe() const
{
	return CraftRecipe;
}

int32 UItemPrimaryDataAsset::GetMaxCraftNum(UInventorySystem* Inventory) 
{
	return CraftRecipe.GetMaxCraftAmount( this, Inventory );
}

bool UItemPrimaryDataAsset::IsCraftable(UInventorySystem* InventorySystem) const
{
	return CraftRecipe.IsCraftable( InventorySystem );
}

bool UItemPrimaryDataAsset::IsEnoughOnCertainItem(const FInventoryItem* Slot) const
{
	return CraftRecipe.IsEnoughOnCertainItem( Slot );
}

void UItemPrimaryDataAsset::Craft(UInventorySystem* InventorySystem)
{
	return CraftRecipe.Craft( this, InventorySystem );
}

