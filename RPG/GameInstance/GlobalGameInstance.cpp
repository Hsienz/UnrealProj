// Fill out your copyright notice in the Description page of Project Settings.


#include "GlobalGameInstance.h"

UMaterial* UGlobalGameInstance::GetBuildPreviewPlaceableMaterial()
{
	return BuildPreviewPlaceableMaterial;
}

UMaterial* UGlobalGameInstance::GetBuildPreviewUnplaceableMaterial()
{
	return BuildPreviewUnplaceableMaterial;
}
