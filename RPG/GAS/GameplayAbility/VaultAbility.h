// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EnhancedGameplayAbility.h"
#include "TraceAbility.h"
#include "VaultAbility.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UVaultAbility : public UTraceAbility
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAnimMontage* VaultMontage;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	int32 LoopCount = 5;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float TraceGap = 50;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float TraceStartOffset = 100;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float TraceLength = 100;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float LandHorizonDistance = 100;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float LandVerticalDistance = 300;
	
	FVector JumpToLocation;

	FVector LandToLocation;

	FVector MidLocation;

	bool JumpToLocationExist;

	bool LandToLocationExist;

public:
	UVaultAbility();
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	virtual void SetupMotionWarping();
	
	bool TraceMain_Implementation(FHitResult& HitResult) override;

};
