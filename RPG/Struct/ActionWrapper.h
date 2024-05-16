// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UObject/Object.h"
#include "ActionWrapper.generated.h"

/**
 * 
 */

USTRUCT( Blueprintable, BlueprintType)
struct FActionWrapper
{
	GENERATED_BODY()
	
	UPROPERTY( EditAnywhere, BlueprintReadOnly)
	UAnimMontage* Montage = nullptr;

	UPROPERTY( EditAnywhere, BlueprintReadOnly)
	float CooldownTime = 1;

	bool bIsCooldown = false;

	FTimerHandle CooldownTimerHandle;
	
};

UCLASS()
class UActionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()

public:

	UFUNCTION(BlueprintCallable)
	static void StartCooldown( FActionWrapper& Action );
	
	UFUNCTION(BlueprintCallable)
	static void CountdownCooldown( UWorld* Object, FActionWrapper& Action );

	UFUNCTION(BlueprintCallable)
	static void StartAndCountdownCooldown( UWorld* Context, FActionWrapper& Action );
};
