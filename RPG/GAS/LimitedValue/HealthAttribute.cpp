// Fill out your copyright notice in the Description page of Project Settings.


#include "HealthAttribute.h"

#include "GameplayEffectExtension.h"
#include "Net/UnrealNetwork.h"
#include "RPG/Interfaces/Damageable.h"
#include "RPG/Interfaces/DamageableActor.h"


void UHealthAttribute::OnAtMinValue_Implementation()
{
	if( IDamageable* DamageableActor = Cast<IDamageable>(GetOwningActor() ) )
	{
		DamageableActor->Execute_HandleDead( GetOwningActor() );
	}
}

void UHealthAttribute::SubHealth(int32 Value)
{
	SetHealth( GetHealth() - Value );
}

void UHealthAttribute::PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data)
{
	Super::PostGameplayEffectExecute(Data);

	if( Data.EvaluatedData.Attribute == GetHealthAttribute() )
	{
		if( GetHealth() <= 0 ) OnAtMinValue();
		SetHealth( FMath::Clamp( GetHealth(), 0, GetMaxHealth()));
		UE_LOG( LogTemp, Log, TEXT("Current Health is: %f"), GetHealth());
	} 
}

void UHealthAttribute::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttribute, Health, COND_None, REPNOTIFY_Always );
	DOREPLIFETIME_CONDITION_NOTIFY(UHealthAttribute, MaxHealth, COND_None, REPNOTIFY_Always );
}

void UHealthAttribute::OnRep_MaxValueChange_Implementation(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY( UHealthAttribute, MaxHealth, OldData );
}

void UHealthAttribute::OnRep_ValueChange_Implementation(const FGameplayAttributeData& OldData)
{
	GAMEPLAYATTRIBUTE_REPNOTIFY( UHealthAttribute, Health, OldData );
}

float UHealthAttribute::GetPercent()
{
	return GetHealth() / GetMaxHealth();
}
