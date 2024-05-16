// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingPartPrimaryDataAsset.h"

TSubclassOf<ABuildingPart> UBuildingPartPrimaryDataAsset::GetBuildingPartClass() const
{
	return BuildingPartClass;
}

EBuildingPartType UBuildingPartPrimaryDataAsset::GetBuildType() const
{
	return BuildType;
}

IUpgradeableAsset* UBuildingPartPrimaryDataAsset::GetNextUpgradableAsset()
{
	return Cast<IUpgradeableAsset>(NextUpgradedAsset);
}
