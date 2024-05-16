// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildingPart.h"

#include "RPG/ActorComponents/ObjectOptionMenu.h"
#include "RPG/PrimaryDataAssets/BuildingPartPrimaryDataAsset.h"

// Sets default values
ABuildingPart::ABuildingPart()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	SceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("Scene"));
	SetRootComponent( SceneComponent );
	
	MeshComponent = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	MeshComponent->SetupAttachment(RootComponent);

	ObjectOptionMenuComponent = CreateDefaultSubobject<UObjectOptionMenu>(TEXT("ObjectOptionMenu"));
}

UStaticMeshComponent* ABuildingPart::GetMesh() const
{
	return MeshComponent;
}

UObjectOptionMenu* ABuildingPart::GetOptionMenuComponent()
{
	return ObjectOptionMenuComponent;
}

IUpgradeableAsset* ABuildingPart::GetCurrentUpgradeableAsset()
{
	return Cast<IUpgradeableAsset>(Asset);
}

void ABuildingPart::Upgrade()
{
	IUpgradeableAsset* NextAssetInterface = GetNextUpgradedAsset();
	if( NextAssetInterface == nullptr ) return;
	UBuildingPartPrimaryDataAsset* NextAsset = Cast<UBuildingPartPrimaryDataAsset>( NextAssetInterface );
	if( NextAsset ) {
		Asset = NextAsset;
		UpdateToAsset();
	}
}

void ABuildingPart::SetAsset(UBuildingPartPrimaryDataAsset* NewAsset)
{
	Asset = NewAsset;
}

void ABuildingPart::UpdateToAsset()
{
	MeshComponent->SetStaticMesh( Asset->GetItemStaticMesh() );
}

// Called when the game starts or when spawned
void ABuildingPart::BeginPlay()
{
	Super::BeginPlay();
}

UBuildingPartPrimaryDataAsset* ABuildingPart::GetBuildingPartAsset()
{
	return Cast<UBuildingPartPrimaryDataAsset>( Asset );
}

void ABuildingPart::Destroyed()
{
	ObjectOptionMenuComponent->CloseMenu();
	Super::Destroyed();
}

// Called every frame
void ABuildingPart::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

