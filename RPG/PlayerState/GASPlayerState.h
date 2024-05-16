// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemInterface.h"
#include "GameFramework/PlayerState.h"
#include "GASPlayerState.generated.h"

class UEnhancedAbilitySystemComponent;
class UStaminaAttribute;
class UHealthAttribute;
class UAbilitySystemComponent;
/**
 * 
 */
UCLASS()
class RPG_API AGASPlayerState : public APlayerState, public IAbilitySystemInterface
{
	GENERATED_BODY()

public:
	AGASPlayerState();

	UPROPERTY(BlueprintReadOnly,VisibleAnywhere)
	UEnhancedAbilitySystemComponent* AbilitySystemComponent;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UHealthAttribute* HealthAttribute;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	UStaminaAttribute* StaminaAttribute;
	
	virtual UAbilitySystemComponent* GetAbilitySystemComponent() const override;
};
