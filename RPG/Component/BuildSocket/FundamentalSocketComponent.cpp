// Fill out your copyright notice in the Description page of Project Settings.


#include "FundamentalSocketComponent.h"

#include "RPG/Actor/BuildingPart.h"
#include "RPG/PrimaryDataAssets/BuildingPartPrimaryDataAsset.h"


// Sets default values for this component's properties
UFundamentalSocketComponent::UFundamentalSocketComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	SocketTypeFlags = Fundamental | Stair;
}


// Called when the game starts
void UFundamentalSocketComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UFundamentalSocketComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                                FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

FVector UFundamentalSocketComponent::GetBaseLocation()
{
	FVector Location = GetComponentLocation();
	Location.Z = Cast<ABuildingPart>( GetOwner() )->GetMesh()->GetComponentLocation().Z;
	return Location;
}

