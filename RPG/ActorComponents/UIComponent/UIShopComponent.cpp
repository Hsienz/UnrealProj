// Fill out your copyright notice in the Description page of Project Settings.


#include "UIShopComponent.h"

#include "RPG/ActorComponents/InventorySystem.h"
#include "RPG/Interfaces/HasInventory.h"
#include "RPG/Struct/ItemSlot.h"
#include "RPG/UserWidgets/Shop/ShopWidget.h"


// Sets default values for this component's properties
UUIShopComponent::UUIShopComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UUIShopComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

bool UUIShopComponent::UpdateUI()
{
	if( !Super::UpdateUI() ) return false;

	UShopWidget* ShopWidget = Cast<UShopWidget>(WidgetPtr.Get());
	
	if( ShopWidget ) {
		ShopWidget->RemoveAllSellingItemFromBox();
	}
	else return false;
	
	if( IHasInventory* HasInventoryActor = Cast<IHasInventory>(GetOwner()))
	{
		
		for( FInventoryItem& SellingItem : HasInventoryActor->GetInventory()->GetInventory() )
		{
			ShopWidget->AddSellingItemToBox( SellingItem );
		}
		
	}
	return true;
}


// Called every frame
void UUIShopComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

