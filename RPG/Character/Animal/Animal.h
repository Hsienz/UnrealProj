// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "Navigation/PathFollowingComponent.h"
#include "RPG/Interfaces/Damageable.h"
#include "RPG/Interfaces/DamageableActor.h"
#include "RPG/Struct/ActionWrapper.h"
#include "Animal.generated.h"

struct FActionWrapper;
class UMontageComponent;
struct FAIRequestID;
class UPawnSensingComponent;


UCLASS()
class RPG_API AAnimal : public ACharacter,
public IDamageableActor,
public IDamageable
{
	GENERATED_BODY()
	
protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UPawnSensingComponent* PawnSensingComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UMontageComponent* MontageComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UHealth* Health;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float RoamDistance = 1000;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	float StopDistance = 100;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FActionWrapper AttackAction;
	
	float OriginalMaxWalkSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	float MaxSprintSpeed;
public:
	// Sets default values for this character's properties
	AAnimal();

	virtual UHealth* GetHealth_Implementation() override;
	
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual void HandleDead_Implementation() override;
	
	FTimerHandle TimerHandle;

	virtual void PreInitializeComponents() override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void RoamAround();

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void OnMoveComplete_Roam( FAIRequestID RequestID, EPathFollowingResult::Type Result);
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void OnMoveComplete_SeePawn( FAIRequestID RequestID, EPathFollowingResult::Type Result);

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void OnSeePawn( APawn* TargetPawn );

	UFUNCTION()
	void HandleAttackNotify( FName NotifyName, const FBranchingPointNotifyPayload& Payload );

	UFUNCTION()
	void HandleAttackMontageEnd(UAnimMontage* Montage, bool bInterrupt);
	
};

