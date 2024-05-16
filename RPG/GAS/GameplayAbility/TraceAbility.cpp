// Fill out your copyright notice in the Description page of Project Settings.


#include "TraceAbility.h"

#include "Kismet/GameplayStatics.h"

bool UTraceAbility::TraceMain_Implementation(FHitResult& HitResult)
{
	return false;
}


bool UTraceAbility::Trace(UObject* WorldContext, const FVector& StartLocation, const FVector& EndLocation, FHitResult& HitResult)
{
	ETraceTypeQuery TraceTypeQuery = UEngineTypes::ConvertToTraceType( ECC_Visibility );
	bool bIsHit = UKismetSystemLibrary::SphereTraceSingle(
		WorldContext,
		StartLocation,
		EndLocation,
		5,
		TraceTypeQuery,
		false,
		{},
		EDrawDebugTrace::ForDuration,
		HitResult,
		true
	);
	return bIsHit;
}
