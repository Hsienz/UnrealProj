// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPG/Interfaces/DamageableActor.h"
#include "Engine/StaticMeshActor.h"
#include "RPG/Interfaces/Damageable.h"
#include "FoliageActor.generated.h"

class USpawnFISMC;
class UInventorySystem;
struct FDropItem;
class UHealth;

UCLASS()
class RPG_API AFoliageActor : public AStaticMeshActor,
public IDamageableActor,
public IDamageable
{
	GENERATED_BODY()


	USpawnFISMC* FoliageRef;	// if use TWeakObjectPtr will throw error, dont know why

	TSet<TWeakObjectPtr<UPrimitiveComponent>> InsideCollision;
public:
	// Sets default values for this actor's properties
	AFoliageActor();

	UPROPERTY( EditAnywhere, BlueprintReadWrite)
	TArray<FDropItem> DropItems;

	virtual UHealth* GetHealth_Implementation() override;

	virtual void HandleDead_Implementation() override;

	void SetFoliageRef(USpawnFISMC* Foliage);

	USpawnFISMC* GetFoliageRef() const;
	
	TSet<TWeakObjectPtr<UPrimitiveComponent>>& GetInsideCollision();
protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void GetDropItem( UInventorySystem* Inventory);

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite)
	UHealth* HealthComponent;
	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;
};
