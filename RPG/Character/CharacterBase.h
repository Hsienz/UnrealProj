// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/Character.h"
#include "CharacterBase.generated.h"

class UEnhancedAbilitySystemComponent;
class UEnhancedGameplayAbility;
class UGameplayEffect;
class UGameplayAbility;

UCLASS()
class RPG_API ACharacterBase : public ACharacter, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	ACharacterBase();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	TWeakObjectPtr<UEnhancedAbilitySystemComponent> AbilitySystemComponentPtr;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<TSubclassOf<UEnhancedGameplayAbility>> Abilities;

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TArray<TSubclassOf<UGameplayEffect>> Effects;

public:
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	virtual void GiveDefaultAbilities();
	
	virtual void ApplyDefaultEffects();
};
