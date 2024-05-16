// Fill out your copyright notice in the Description page of Project Settings.


#include "EnhancedAbilitySystemComponent.h"

#include "EnhancedInputComponent.h"
#include "RPG/GAS/GameplayAbility/EnhancedGameplayAbility.h"


// Sets default values for this component's properties
UEnhancedAbilitySystemComponent::UEnhancedAbilitySystemComponent()
{
}
void UEnhancedAbilitySystemComponent::BindAbilityActivationToInputComponent(UInputComponent* InputComponent, FGameplayAbilityInputBinds BindInfo)
{
	UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(InputComponent);
	if( !EnhancedInputComponent ) return;
	
	SetBlockAbilityBindingsArray(BindInfo);
	
	for( FGameplayAbilitySpec& Spec : GetActivatableAbilities() )
	{
		if( UEnhancedGameplayAbility* Ability = Cast<UEnhancedGameplayAbility> (Spec.Ability.Get()) )
		{
			EnhancedInputComponent->BindAction( Ability->GetInputAction(), ETriggerEvent::Started, this, &UEnhancedAbilitySystemComponent::AbilityLocalInputPressed, Spec.InputID );
			EnhancedInputComponent->BindAction( Ability->GetInputAction(), ETriggerEvent::Completed, this, &UEnhancedAbilitySystemComponent::AbilityLocalInputReleased, Spec.InputID );
		}
	}
}
