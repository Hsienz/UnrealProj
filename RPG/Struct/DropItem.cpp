// Fill out your copyright notice in the Description page of Project Settings.


#include "DropItem.h"

#include "ItemSlot.h"
#include "RPG/ActorComponents/InventorySystem.h"

int32 FDropItem::GetRandomAmount() const 
{
	if( FMath::RandRange(0.f,1.f) > FirstUnderPossibility ) return 0;
	int32 Res = 0;
	float RandomFloat = FMath::RandRange(0.f, 1.f );
	switch (CollectMethod)
	{
	case Fixed:
		Res = MinAmount;
		break;
	case Dynamic:
		Res = FMath::Min( MaxAmount , MinAmount + FMath::LogX( Possibility, RandomFloat ) );
		break;
	case Random:
		Res = FMath::RandRange( MinAmount, MaxAmount );
		break;
	}
	return Res;
}

FInventoryItem FDropItem::GetSlotWidthRandomAmount() const
{
	FInventoryItem Res;
	Res.ItemAsset = Item;
	Res.Stack = GetRandomAmount();
	return Res;
}

