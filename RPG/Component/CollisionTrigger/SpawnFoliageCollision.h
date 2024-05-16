// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollisionTriggerComponent.h"
#include "Components/ActorComponent.h"
#include "SpawnFoliageCollision.generated.h"


class AFoliageActor;
class USpawnFISMC;
class USphereComponent;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API USpawnFoliageCollision : public UCollisionTriggerComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	USpawnFoliageCollision();
	
	static AFoliageActor* ReplaceFoliageToActor(USpawnFISMC* Foliage, int32 Index);

	static int32 ReplaceActorToFoliage(AFoliageActor* Actor);

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnCollisionBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;
	
	virtual void OnCollisionEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;


public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};


