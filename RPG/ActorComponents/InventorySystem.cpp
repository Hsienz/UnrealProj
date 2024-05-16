// Fill out your copyright notice in the Description page of Project Settings.


#include "InventorySystem.h"

#include "EnhancedInputComponent.h"
#include "ScreenComponent.h"
#include "RPG/Character/PlayerCharacter.h"
#include "RPG/PrimaryDataAssets/ItemPrimaryDataAsset.h"
#include "RPG/Struct/DropItem.h"
#include "RPG/Struct/ItemSlot.h"
#include "UIComponent/UIInventoryComponent.h"



// Sets default values for this component's properties
UInventorySystem::UInventorySystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

void UInventorySystem::AddItem(UItemPrimaryDataAsset* Item, int32 Amount)
{
	while( Amount )
	{
		TSharedPtr<FInventoryItem> Slot = GetNotFullInventorySlot( Item );
		if( Slot == nullptr )
		{
			FInventoryItem NewSlot;
			NewSlot.ItemAsset = Item;
			Inventory.Add( NewSlot );
			Slot = MakeShared<FInventoryItem>( Inventory.Last() );
		}
		int32 TrueAmount = FMath::Min( Item->GetMaxStack() - Slot->Stack, Amount );
		Slot->Stack += TrueAmount;
		Amount -= TrueAmount;
	}
}

void UInventorySystem::AddItem( const FDropItem& DropItem)
{
	UE_LOG( LogTemp, Warning, TEXT("Get:%s"), *DropItem.Item->GetItemName().ToString() );
	UE_LOG( LogTemp, Log, TEXT("%d"), DropItem.GetRandomAmount() );
	AddItem( DropItem.Item, DropItem.GetRandomAmount() );
}

void UInventorySystem::AddItem(const FInventoryItem& ItemSlot)
{
	AddItem( ItemSlot.ItemAsset, ItemSlot.Stack );
}

void UInventorySystem::AddEmpty(int32 Amount)
{
	while( Amount-- )
	{
		Inventory.Add( FInventoryItem() );
	}
}


TSharedPtr<FInventoryItem> UInventorySystem::GetNotFullInventorySlot(UItemPrimaryDataAsset* Item)
{
	int32 Index = GetNotFullInventorySlotIndex( Item );
	if( Index == -1 ) return nullptr;
	return MakeShared<FInventoryItem>(Inventory[Index]);
}

int32 UInventorySystem::GetInventorySlotIndex(UItemPrimaryDataAsset* Item, EInventorySearchMethod Method)
{
	int32 Res = -1;
	for( int32 i = 0 ; i < Inventory.Num(); i++ )
	{
		bool Finish = false;
		if( Inventory[i].ItemAsset == Item )
		{
			switch ( Method )
			{
			case EInventorySearchMethod::First:
				Res = i;
				Finish = true;
				break;
			case EInventorySearchMethod::FirstNotFull:
				if( Inventory[i].Stack < Item->GetMaxStack() )
				{
					Res = i;
					Finish = true;
				}
				break;
			}
		}
		if( Finish ) break;
	}
	return Res;
}

int32 UInventorySystem::GetNotFullInventorySlotIndex(UItemPrimaryDataAsset* Item)
{
	return GetInventorySlotIndex( Item, EInventorySearchMethod::FirstNotFull );
}

int32 UInventorySystem::GetItemAmount(UItemPrimaryDataAsset* Item)
{
	int32 Res = 0;
	for( int32 i = 0; i < Inventory.Num(); i++ )
	{
		if( Inventory[i].ItemAsset == Item )
		{
			Res += Inventory[i].Stack;
		}
	}
	return Res;
}

void UInventorySystem::RemoveItemAmount(UItemPrimaryDataAsset* Item, int32 Amount)
{
	while ( Amount )
	{
		int32 Index = GetInventorySlotIndex( Item );
		if( Index == -1 )
		{
			UE_LOG( LogTemp, Warning, TEXT("Item not sufficant"));
			break;
		}
		FInventoryItem& Slot = Inventory[Index];
		int32 TrueAmount = FMath::Min( Slot.Stack, Amount );
		Slot.Stack -= TrueAmount;
		if( Slot.Stack == 0 )
		{
			Inventory[Index].ItemAsset = nullptr;
		}
	}
}

TSharedPtr<FInventoryItem> UInventorySystem::GetInventorySlot(UItemPrimaryDataAsset* Item,
                                                              EInventorySearchMethod Method)
{
	if( int32 Index = GetInventorySlotIndex(Item,Method) != -1 )
	{
		return MakeShared<FInventoryItem>(Inventory[Index]);
	}
	return nullptr;
}

TArray<FInventoryItem>& UInventorySystem::GetInventory()
{
	return Inventory;
}

TSharedRef<FInventoryItem> UInventorySystem::GetInventoryItem(int32 Index)
{
	return MakeShared<FInventoryItem>( Inventory[Index] );
}

void UInventorySystem::ToggleInventoryMenu()
{
	Cast<APlayerCharacter>(GetOwner())->GetUIInventory()->ToggleUI();
}

// Called when the game starts
void UInventorySystem::BeginPlay()
{
	Super::BeginPlay();
}

void UInventorySystem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if( UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent) )
	{
		EnhancedInputComponent->BindAction( OpenMenuAction, ETriggerEvent::Started, this, &UInventorySystem::ToggleInventoryMenu );
	}
}

FInventoryItem UInventorySystem::operator[](int32 Index) const
{
	return Inventory[Index];
}

FInventoryItem& UInventorySystem::operator[](int32 Index)
{
	return Inventory[Index];
}


// Called every frame
void UInventorySystem::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

