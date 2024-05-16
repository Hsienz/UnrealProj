// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "TraceAbility.h"
#include "DodgeAbility.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UDodgeAbility : public UTraceAbility
{
	GENERATED_BODY()
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAnimMontage* DodgeMontage;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool CanCrossThruGap;
public:

	UDodgeAbility();

	virtual bool TraceMain_Implementation(FHitResult& HitResult) override;

	bool TraceHV(const FVector& Direction, FHitResult& HitResult);

	bool TraceV(const FVector& StartLocation, FHitResult& HitResult);
	
	virtual void ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData) override;

	virtual void EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled) override;

	void SetupDodgeMotionWarping(const FVector& LandLocation);
};
