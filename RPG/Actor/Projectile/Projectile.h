// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "RPG/Actor/ItemBase.h"
#include "RPG/Actor/Weapon.h"
#include "Projectile.generated.h"

class UArrowComponent;
class UProjectileMovementComponent;

UCLASS()
class RPG_API AProjectile : public AWeapon
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UProjectileMovementComponent* ProjectileMovementComponent;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess))
	UArrowComponent* TraceCenter;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	FName ProjectileProfileName = "Projectile";

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	float DestroyAfterSec;
public:
	// Sets default values for this actor's properties
	AProjectile();

protected:
	bool bLaunched;

	bool bIsHit;

	FVector PrevPosition;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	virtual void ProjectileHit( const FHitResult& HitTarget );

	FTimerHandle DestroyTimerHandle;
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UFUNCTION(BlueprintCallable)
	virtual void Launch();

	virtual void NatualDestroy();

	virtual void SetCharacterRef(ACharacter* Character) override;


	virtual void DamageTrace_Implementation() override;
};
