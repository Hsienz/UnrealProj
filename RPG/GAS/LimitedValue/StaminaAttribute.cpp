// Fill out your copyright notice in the Description page of Project Settings.


#include "StaminaAttribute.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"

void UStaminaAttribute::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if( Data.EvaluatedData.Attribute == GetStaminaAttribute() )
	{
		SetStamina( FMath::Clamp( GetStamina(), 0, GetMaxStamina()));
	} 
}

void UStaminaAttribute::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UStaminaAttribute, Stamina, COND_None, REPNOTIFY_Always );
	DOREPLIFETIME_CONDITION_NOTIFY(UStaminaAttribute, MaxStamina, COND_None, REPNOTIFY_Always );
}

void UStaminaAttribute::OnRep_MaxValueChange_Implementation(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY( UStaminaAttribute, MaxStamina, OldData );
}

void UStaminaAttribute::OnRep_ValueChange_Implementation(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY( UStaminaAttribute, Stamina, OldData );
}

float UStaminaAttribute::GetPercent()
{
	return GetStamina() / GetMaxStamina();
}
