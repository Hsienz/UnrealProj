// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "MontageComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UMontageComponent : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UMontageComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	UFUNCTION(Server,Reliable)
	void ServerMulticastMontagePlay(
		UAnimMontage* Montage,
		float InPlayRate = 1,
		EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength,
		float InTimeToStartMontageAt = 0, bool bStopAllMontage = true
	);

	UFUNCTION(NetMulticast,Reliable)
	void MulticastMontagePlay(
		UAnimMontage* Montage,
		float InPlayRate = 1,
		EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength,
		float InTimeToStartMontageAt = 0, bool bStopAllMontage = true
	);

	float MontagePlay(
		UAnimMontage* Montage,
		float InPlayRate = 1,
		EMontagePlayReturnType ReturnValueType = EMontagePlayReturnType::MontageLength,
		float InTimeToStartMontageAt = 0, bool bStopAllMontage = true
	);
	
	UAnimInstance* GetAnimInstance() const;
};
