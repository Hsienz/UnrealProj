// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSlot.h"


FInventoryItem::FInventoryItem()
{
	
}

FInventoryItem::FInventoryItem(UItemPrimaryDataAsset* ItemAsset, int32 Stack)
{
	this->ItemAsset = ItemAsset;
	this->Stack = Stack;
}
