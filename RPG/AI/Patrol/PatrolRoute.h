// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PatrolRoute.generated.h"

class USplineComponent;

UCLASS()
class RPG_API APatrolRoute : public AActor
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	USplineComponent* PatrolRoute;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	int32 PointIndexOnRoute;

	// Direction: 1 - forward, -1 - backward
	int8 Direction = 1;
public:
	// Sets default values for this actor's properties
	APatrolRoute();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION( BlueprintCallable )
	FVector GetPointLocationInWorld();

	UFUNCTION( BlueprintCallable )
	void MoveForwardToNextPoint();

	UFUNCTION(BlueprintCallable)
	void MoveBackwardToPrevPoint();

	UFUNCTION(BlueprintCallable)
	void ChangeDirection();

	void UpdatePointIndexAlongDirection();
};
