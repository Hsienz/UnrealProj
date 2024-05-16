// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AbilitySystemComponent.h"
#include "AttributeSet.h"
#include "AttributeSetUtil.h"
#include "StaminaAttribute.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UStaminaAttribute : public UAttributeSet
{
	GENERATED_BODY()
protected:
	UPROPERTY( EditAnywhere,BlueprintReadOnly,ReplicatedUsing=OnRep_ValueChange )
	FGameplayAttributeData Stamina = 0.5;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,ReplicatedUsing=OnRep_MaxValueChange)
	FGameplayAttributeData MaxStamina = 1;

public:
	ATTRIBUTE_ACCESSORS(UStaminaAttribute,Stamina);
	ATTRIBUTE_ACCESSORS(UStaminaAttribute,MaxStamina);

	virtual void PostGameplayEffectExecute(const FGameplayEffectModCallbackData& Data) override;

	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void OnRep_MaxValueChange(const FGameplayAttributeData& OldData);

	UFUNCTION(BlueprintNativeEvent,BlueprintCallable)
	void OnRep_ValueChange(const FGameplayAttributeData& OldData);

	UFUNCTION(BlueprintCallable)
	virtual float GetPercent();
};
