// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "GlobalGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UGlobalGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly, Category="Build", meta=(AllowPrivateAccess) )
	UMaterial* BuildPreviewPlaceableMaterial;
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly,	Category="Build", meta=(AllowPrivateAccess) )
	UMaterial* BuildPreviewUnplaceableMaterial;

public:
	UMaterial* GetBuildPreviewPlaceableMaterial();

	UMaterial* GetBuildPreviewUnplaceableMaterial();
};
