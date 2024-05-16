// Fill out your copyright notice in the Description page of Project Settings.


#include "PatrolRoute.h"

#include "Components/SplineComponent.h"


// Sets default values
APatrolRoute::APatrolRoute()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	PatrolRoute = CreateDefaultSubobject<USplineComponent>(TEXT("PatrolRoute"));
	PatrolRoute->SetupAttachment( RootComponent );
}

// Called when the game starts or when spawned
void APatrolRoute::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APatrolRoute::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

FVector APatrolRoute::GetPointLocationInWorld()
{
	return PatrolRoute->GetLocationAtSplinePoint( PointIndexOnRoute, ESplineCoordinateSpace::World );
}

void APatrolRoute::MoveForwardToNextPoint()
{
	UpdatePointIndexAlongDirection();
}

void APatrolRoute::MoveBackwardToPrevPoint()
{
	ChangeDirection();
	MoveForwardToNextPoint();
}

void APatrolRoute::ChangeDirection()
{
	Direction *= -1;
}

void APatrolRoute::UpdatePointIndexAlongDirection()
{
	int32 NextPos=  PointIndexOnRoute + Direction;
	if( NextPos < 0 || NextPos >= PatrolRoute->GetNumberOfSplinePoints() ) ChangeDirection();
	PointIndexOnRoute += Direction;
}

