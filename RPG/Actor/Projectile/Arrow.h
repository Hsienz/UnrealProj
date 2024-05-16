// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Projectile.h"
#include "Arrow.generated.h"

UCLASS()
class RPG_API AArrow : public AProjectile
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AArrow();
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void TraceOnShield_Implementation(AShield* Shield) override;
};
