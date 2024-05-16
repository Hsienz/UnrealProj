// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Abilities/GameplayAbility.h"
#include "EnhancedGameplayAbility.generated.h"

class UInputAction;

UENUM(Blueprintable)
enum class EGameplayAbilityBindingType : uint8
{
	None,
	CancelTarget,
	ConfirmTarget,
	Sprint,
	Vault,
	Dodge,
	Jump,
};


UCLASS()
class RPG_API UEnhancedGameplayAbility : public UGameplayAbility
{
	GENERATED_BODY()

protected:

	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	EGameplayAbilityBindingType AbilityBindingId;
	
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	UInputAction* InputAction;

public:
	EGameplayAbilityBindingType GetAbilityBindingId() const;

	UInputAction* GetInputAction() const;

};
