// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPG/Struct/Combo/ComboSequence.h"
#include "ComboSystem.generated.h"


struct FComboSequence;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UComboSystem : public UActorComponent
{
	GENERATED_BODY()

	// record the smart pointer of combo sequence, use this to determine if pointer is valid
	TSharedPtr<FComboSequence> LatestComboSharedPtr;
	
	// record the raw pointer of combo sequence, use this to compare if the sequence is same
	FComboSequence* LatestComboPtr;

	int32 ComboIndex;

	// a set to record which actor is hit by a combo, so that the damage wont count duplicate
	UPROPERTY()
	TSet<AActor*> HitActor;
protected:
	
	UPROPERTY(BlueprintReadWrite,EditAnywhere)
	bool bIsLock;
	
public:
	// Sets default values for this component's properties
	UComboSystem();
	
	void ProcessCombo(FComboSequence& ComboSequence, bool bLock = true);

	void LockCombo();

	UFUNCTION(BlueprintCallable)
	void UnlockCombo();

	UFUNCTION(BlueprintCallable)
	void ResetCombo();

	UFUNCTION(BlueprintCallable)
	void ClearHitActor();

	UFUNCTION(BlueprintCallable)
	void AddHitActor(AActor* Actor);
	
	UFUNCTION(BlueprintCallable)
	bool IsActorHit(AActor* Actor);
	
	void NextCombo();
	
	void ProcessCheckSameComboSequenceAndSet(FComboSequence& ComboSequence);
};
