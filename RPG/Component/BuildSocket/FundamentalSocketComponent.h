﻿// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "SocketComponent.h"
#include "Components/BoxComponent.h"
#include "FundamentalSocketComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UFundamentalSocketComponent : public USocketComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UFundamentalSocketComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual FVector GetBaseLocation() override;
};
