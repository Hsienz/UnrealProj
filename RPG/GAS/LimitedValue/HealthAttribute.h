// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSetUtil.h"
#include "AttributeSet.h"
#include "HealthAttribute.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UHealthAttribute : public UAttributeSet
{
	GENERATED_BODY()
protected:
	UPROPERTY( EditAnywhere,BlueprintReadOnly,ReplicatedUsing=OnRep_ValueChange )
	FGameplayAttributeData Health = 0.5;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,ReplicatedUsing=OnRep_MaxValueChange)
	FGameplayAttributeData MaxHealth = 1;

public:
	ATTRIBUTE_ACCESSORS(UHealthAttribute,Health);
	ATTRIBUTE_ACCESSORS(UHealthAttribute,MaxHealth);
	
	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void OnAtMinValue();

	void SubHealth( int32 Value );

	
	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void OnRep_MaxValueChange(const FGameplayAttributeData& OldData);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void OnRep_ValueChange(const FGameplayAttributeData& OldData);

	UFUNCTION(BlueprintCallable)
	virtual float GetPercent();
};
