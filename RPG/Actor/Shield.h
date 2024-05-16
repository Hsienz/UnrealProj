// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Weapon.h"
#include "Shield.generated.h"

UCLASS()
class RPG_API AShield : public AWeapon
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AShield();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	bool bIsHoldingShield;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAnimMontage* HoldingShieldMontage;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void RightUse_Implementation() override;

	void HoldShield();

	void ReleaseShield();

	void RightRelease();

	UAnimMontage* GetHoldingShieldMontage() const;
};


