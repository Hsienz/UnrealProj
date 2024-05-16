// Fill out your copyright notice in the Description page of Project Settings.


#include "WallSocketComponent.h"

#include "RPG/PrimaryDataAssets/BuildingPartPrimaryDataAsset.h"


// Sets default values for this component's properties
UWallSocketComponent::UWallSocketComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SocketTypeFlags |= Wall;
	// ...
}

FVector UWallSocketComponent::GetBaseLocation()
{
	FVector Location = GetComponentLocation();
	Location.Z -= GetRelativeLocation().Z / 2;
	return Location;
}


// Called when the game starts
void UWallSocketComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UWallSocketComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                         FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

