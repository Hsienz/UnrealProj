// Fill out your copyright notice in the Description page of Project Settings.


#include "TreeFoliageActor.h"

#include "RPG/Struct//DropItem.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "RPG/Interfaces/HasInventory.h"
#include "RPG/ActorComponents/LimitedValue/Health.h"


// Sets default values
ATreeFoliageActor::ATreeFoliageActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent->SetValue( Max, 4);
	HealthComponent->SetValue( Current, 4);
}

// Called when the game starts or when spawned
void ATreeFoliageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ATreeFoliageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

