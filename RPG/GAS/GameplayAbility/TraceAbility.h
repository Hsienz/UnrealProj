// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedGameplayAbility.h"
#include "TraceAbility.generated.h"

/**
 * 
 */

USTRUCT(BlueprintType)
struct FTraceInfo
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxVerticalDistance = 300;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float VerticalOffset = 100;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float TraceGap = 100;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int32 TraceCount = 5;
};

UCLASS()
class RPG_API UTraceAbility : public UEnhancedGameplayAbility
{
	GENERATED_BODY()

protected:
	FTraceInfo TraceInfo;

	// FHitResult HitResult;

public:

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	bool TraceMain(FHitResult& HitResult);

	bool Trace( const FVector& OriginStartLocation, FHitResult& HitResult, const FTraceInfo& TraceInfo );
	
	static bool Trace(UObject* WorldContext, const FVector& StartLocation, const FVector& EndLocation, FHitResult& HitResult);
};


