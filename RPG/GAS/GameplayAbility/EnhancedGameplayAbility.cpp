// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedGameplayAbility.h"

EGameplayAbilityBindingType UEnhancedGameplayAbility::GetAbilityBindingId() const
{
	return AbilityBindingId;
}

UInputAction* UEnhancedGameplayAbility::GetInputAction() const
{
	return InputAction;
}
