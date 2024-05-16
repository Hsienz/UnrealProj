// Fill out your copyright notice in the Description page of Project Settings.


#include "UIInventoryComponent.h"

#include "RPG/Interfaces/HasInventory.h"
#include "RPG/UserWidgets/InventoryMenu.h"


// Sets default values for this component's properties
UUIInventoryComponent::UUIInventoryComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UUIInventoryComponent::BeginPlay()
{
	Super::BeginPlay();
	CreateUI();
}

bool UUIInventoryComponent::UpdateUI()
{
	if( !Super::UpdateUI() ) return false;

	UInventoryMenu* InventoryMenu = Cast<UInventoryMenu>(WidgetPtr.Get());

	if( InventoryMenu ) InventoryMenu->UpdateItemSlotGrid();
	else return false;
	
	return true;
}


// Called every frame
void UUIInventoryComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

