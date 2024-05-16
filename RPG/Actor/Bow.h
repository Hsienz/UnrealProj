// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Bow.generated.h"

class UArrowComponent;
class AArrow;
class UPoseableMeshComponent;

UCLASS()
class RPG_API ABow : public AWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	TSubclassOf<AArrow> BP_Projectile;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UArrowComponent* ArrowOutLocation;
	
	int32 Accumulation;

	UPROPERTY(Replicated)
	bool bIsAiming;

public:
	// Sets default values for this actor's properties
	ABow();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAnimMontage* DrawArrowMontage;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAnimMontage* ShootArrowMontage;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FName StringName = "String";

	TWeakObjectPtr<AArrow> ArrowActor;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
	virtual void LeftUse_Implementation() override;;

	virtual void RightUse_Implementation() override;

	
	UFUNCTION()
	virtual void OnPlayMontageNotifyBegin_AttachString( FName Name, const FBranchingPointNotifyPayload& Payload);

	UFUNCTION()
	virtual void OnMontageEnded_StartAiming( UAnimMontage* Montage, bool bInterrupted );

	UFUNCTION()
	virtual void AfterShoot( UAnimMontage* Montage, bool bInterrupted );

	void SpawnArrow();

	virtual void AttachStringToOtherHand();

	virtual void ArrowRelocation();

	void StartAiming();

	void StopAiming();

	
	UFUNCTION(BlueprintCallable)
	bool IsAiming() const;
	
	virtual void DrawArrow();

	void ShootArrow();

	void ResetString();

};

