// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/Character.h"
#include "RPG/AI/Patrol/Interface/HasPatrolRoute.h"
#include "RPG/Interfaces/Damageable.h"
#include "RPG/Interfaces/DamageableActor.h"
#include "RPG/Interfaces/DamageableGasActor.h"
#include "RPG/Interfaces/HasMontageComponent.h"
#include "Enemy.generated.h"

class UAIPerceptionComponent;
class APatrolRoute;
class UHealthAttribute;
class UWidgetComponent;
class UHealth;
class UStatusBarWidget;

UCLASS()
class RPG_API AEnemy :
public ACharacterBase,
public IDamageable,
public IDamageableGasActor,
public IHasMontageComponent,
public IHasPatrolRoute

{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AEnemy();

	TSubclassOf<UStatusBarWidget> HealthBar;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UMontageComponent* MontageComponent;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UEnhancedAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UHealthAttribute* HealthAttribute;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UWidgetComponent* InfoWidgetComponent;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UAnimMontage* DeadAnim;

	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TObjectPtr<APatrolRoute> PatrolRoute;

	virtual void HandleDead_Implementation() override;

	virtual float TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser) override;

	virtual void PostInitializeComponents() override;

	virtual UMontageComponent* GetMontageSystem_Implementation() const override;

	FTimerHandle DeathTimerHandle;
	
	UFUNCTION(BlueprintCallable, BlueprintNativeEvent)
	void AfterDead();
	
	UFUNCTION()
	void DeadAnimEndDelegate( UAnimMontage* Anim, bool bIsInterrupt);

	
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual UHealthAttribute* GetHealthAttribute_Implementation() const override;

	UWidgetComponent* GetInfoWidgetComponent() const;

	virtual APatrolRoute* GetPatrolRoute_Implementation() override;
};

