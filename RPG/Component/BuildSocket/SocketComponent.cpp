// Fill out your copyright notice in the Description page of Project Settings.


#include "SocketComponent.h"

#include "RPG/PrimaryDataAssets/BuildingPartPrimaryDataAsset.h"


// Sets default values for this component's properties
USocketComponent::USocketComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

int32 USocketComponent::GetSocketType() const
{
	return SocketTypeFlags;
}

FVector USocketComponent::GetBaseLocation()
{
	return GetComponentLocation();
}

FRotator USocketComponent::GetBaseRotation()
{
	return GetComponentRotation();
}


// Called when the game starts
void USocketComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


bool USocketComponent::IsInSocketTypeFlags(EBuildingPartType Type)
{
	UE_LOG( LogTemp, Log, TEXT("%d,%d"), SocketTypeFlags, Type);
	return SocketTypeFlags & (1<<Type) ;
}

// Called every frame
void USocketComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

