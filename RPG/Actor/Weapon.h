// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ItemBase.h"
#include "RPG/Struct/Combo/ComboSequence.h"
#include "Weapon.generated.h"

class AShield;
class UGameplayEffect;
class UComboSystem;
struct FComboSequence;

UCLASS()
class RPG_API AWeapon : public AItemBase
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AWeapon();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	FComboSequence Combos;
	
	FTimerHandle DamageTraceHandle;

	TWeakObjectPtr<UComboSystem> ComboSystem;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	float DamageTraceRate = .01;
public:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UGameplayEffect> DealDamageEffect;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void LeftUse_Implementation() override;

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StartDamageTrace();
	
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void DamageTrace();

	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void StopDamageTrace();

	UFUNCTION(BlueprintCallable)
	void TryApplyDamageToTarget( AActor* Actor );

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void TraceOnShield( AShield* Shield );


	bool DetermineIfTraceOnShieldBeforeApplyDamage( AActor* Actor );
};
