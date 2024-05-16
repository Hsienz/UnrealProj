// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnFISMC.h"

#include "RPG/Actor/Foliage/FoliageActor.h"

TSubclassOf<AFoliageActor> USpawnFISMC::GetFoliageActor() const
{
	return FoliageActor;
}

bool USpawnFISMC::IsCollisionSpawnable() const
{
	return bIsCollisionSpawnable;
}

