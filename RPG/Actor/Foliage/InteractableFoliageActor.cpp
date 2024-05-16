// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableFoliageActor.h"

#include "Kismet/GameplayStatics.h"


// Sets default values
AInteractableFoliageActor::AInteractableFoliageActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

TArray<FInteraction>& AInteractableFoliageActor::GetInteractions()
{
	return Interactions;
}


// Called when the game starts or when spawned
void AInteractableFoliageActor::BeginPlay()
{
	Super::BeginPlay();
	
}


// Called every frame
void AInteractableFoliageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

