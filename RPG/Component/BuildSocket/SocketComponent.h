// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/BoxComponent.h"
#include "SocketComponent.generated.h"


enum EBuildingPartType : int32;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API USocketComponent : public UBoxComponent
{
	GENERATED_BODY()


public:
	// Sets default values for this component's properties
	USocketComponent();

	int32 GetSocketType() const;

	bool IsInSocketTypeFlags( EBuildingPartType Type );
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(Bitmask, BitmaskEnum = "/Script/BuildingGame.EBuildingPartType"))
	int32 SocketTypeFlags;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual FVector GetBaseLocation();

	virtual FRotator GetBaseRotation();
};
