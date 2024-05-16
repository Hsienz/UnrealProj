// Fill out your copyright notice in the Description page of Project Settings.


#include "GASPlayerState.h"

#include "AbilitySystemComponent.h"
#include "RPG/GAS/AbilitySystemComponent/EnhancedAbilitySystemComponent.h"
#include "RPG/GAS/LimitedValue/HealthAttribute.h"
#include "RPG/GAS/LimitedValue/StaminaAttribute.h"

AGASPlayerState::AGASPlayerState()
{
	AbilitySystemComponent = CreateDefaultSubobject<UEnhancedAbilitySystemComponent>(TEXT("AbilitySystemComponent"));
	AbilitySystemComponent->SetIsReplicated(true);
	AbilitySystemComponent->SetReplicationMode( EGameplayEffectReplicationMode::Mixed );

	HealthAttribute = CreateDefaultSubobject<UHealthAttribute>(TEXT("HealthAttribute"));
	StaminaAttribute = CreateDefaultSubobject<UStaminaAttribute>(TEXT("StaminaAttribute"));
	
}

UAbilitySystemComponent* AGASPlayerState::GetAbilitySystemComponent() const
{
	return Cast<UAbilitySystemComponent>(AbilitySystemComponent);
}
