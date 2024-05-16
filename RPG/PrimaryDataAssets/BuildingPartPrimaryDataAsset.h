// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemPrimaryDataAsset.h"
#include "RPG/Interfaces/UpgradeableAsset.h"
#include "Engine/DataAsset.h"
#include "BuildingPartPrimaryDataAsset.generated.h"

class ABuildingPart;

UENUM(BlueprintType, meta=(Bitflags, UseEnumValueAsMaskValueInEditor ))
enum EBuildingPartType : int32
{
	None		= 0,
	Fundamental = 1 << 0,
	Wall		= 1 << 1,
	Door		= 1 << 2,
	Window		= 1 << 3,
	DoorFrame	= 1 << 4,
	Triangle	= 1 << 5,
	Celling		= 1 << 6,
	Stair		= 1 << 7
};
ENUM_CLASS_FLAGS( EBuildingPartType );
/**
 * 
 */
UCLASS()
class RPG_API UBuildingPartPrimaryDataAsset : public UItemPrimaryDataAsset, public IUpgradeableAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	UBuildingPartPrimaryDataAsset* NextUpgradedAsset;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess))
	TSubclassOf<ABuildingPart> BuildingPartClass;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	TEnumAsByte<EBuildingPartType> BuildType;
	
public:

	UMaterial* GetBuildingPartMaterial() const;

	TSubclassOf<ABuildingPart> GetBuildingPartClass() const;

	EBuildingPartType GetBuildType() const;

	virtual IUpgradeableAsset* GetNextUpgradableAsset() override;
};
