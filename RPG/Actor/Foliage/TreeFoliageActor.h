// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoliageActor.h"
#include "TreeFoliageActor.generated.h"

UCLASS()
class RPG_API ATreeFoliageActor : public AFoliageActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ATreeFoliageActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
