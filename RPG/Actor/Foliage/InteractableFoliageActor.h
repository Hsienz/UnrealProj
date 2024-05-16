// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoliageActor.h"
#include "RPG/Interfaces/Interactable.h"
#include "InteractableFoliageActor.generated.h"

UCLASS()
class RPG_API AInteractableFoliageActor : public AFoliageActor, public IInteractable
{
	GENERATED_BODY()

	TArray<FInteraction> Interactions;
	
public:
	// Sets default values for this actor's properties
	AInteractableFoliageActor();

	virtual TArray<FInteraction>& GetInteractions() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
