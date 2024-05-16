// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "GameFramework/Actor.h"
#include "RPG/Interfaces/HasObjectOptionMenu.h"
#include "RPG/Interfaces/UpgradeableObject.h"
#include "BuildingPart.generated.h"

class UBuildingPartPrimaryDataAsset;


UCLASS()
class RPG_API ABuildingPart : public AItemBase, public IHasObjectOptionMenu, public IUpgradeableObject
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	USceneComponent* SceneComponent;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess))
	UStaticMeshComponent* MeshComponent;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UObjectOptionMenu* ObjectOptionMenuComponent;

public:	
	// Sets default values for this actor's properties
	ABuildingPart();

	UStaticMeshComponent* GetMesh() const;

	virtual UObjectOptionMenu* GetOptionMenuComponent() override;

	virtual IUpgradeableAsset* GetCurrentUpgradeableAsset() override;
	
	virtual void Upgrade() override;

	void SetAsset( UBuildingPartPrimaryDataAsset* NewAsset );

	void UpdateToAsset();

	virtual void Destroyed() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual UBuildingPartPrimaryDataAsset* GetBuildingPartAsset();
public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
