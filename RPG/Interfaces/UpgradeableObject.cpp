// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeableObject.h"

#include "UpgradeableAsset.h"


// Add default functionality here for any IUpgradeableObject functions that are not pure virtual.

IUpgradeableAsset* IUpgradeableObject::GetNextUpgradedAsset()
{
	return GetCurrentUpgradeableAsset()->GetNextUpgradableAsset();
}
