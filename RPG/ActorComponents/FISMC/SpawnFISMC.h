// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "FoliageInstancedStaticMeshComponent.h"
#include "SpawnFISMC.generated.h"

class AFoliageActor;
/**
 * 
 */
UCLASS()
class RPG_API USpawnFISMC : public UFoliageInstancedStaticMeshComponent
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	bool bIsCollisionSpawnable;

protected:
	UPROPERTY( BlueprintReadWrite, EditAnywhere)
	TSubclassOf<AFoliageActor> FoliageActor;
public:
	TSubclassOf<AFoliageActor> GetFoliageActor() const;

	bool IsCollisionSpawnable() const;

};
