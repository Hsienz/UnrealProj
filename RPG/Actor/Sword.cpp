// Fill out your copyright notice in the Description page of Project Settings.


#include "Sword.h"


// Sets default values
ASword::ASword()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;;
}

void ASword::PlayEquipmentMontageNotifyBegin(const FName NotifyName,
	const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::PlayEquipmentMontageNotifyBegin(NotifyName, BranchingPointPayload);
	if( NotifyName == "HoldingSword" ) {
		SetActorHiddenInGame( false );
	}
}

void ASword::PlayUnequipmentMontageNotifyBegin(const FName NotifyName,
	const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	Super::PlayUnequipmentMontageNotifyBegin(NotifyName, BranchingPointPayload);
	UE_LOG( LogTemp, Log, TEXT("%s"), *NotifyName.ToString());
	if( NotifyName == "SheathSword")
	{
		Destroy();
	}
}

