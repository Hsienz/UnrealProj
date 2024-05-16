// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "IMCActorComponent.generated.h"


class UEnhancedInputLocalPlayerSubsystem;
class UInputMappingContext;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UIMCActorComponent : public UActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input",meta=(AllowPrivateAccess))
	UInputMappingContext* InputMappingContext;

	UPROPERTY(EditDefaultsOnly,BlueprintReadOnly,Category="Input",meta=(AllowPrivateAccess))
	int32 InputMappingContextPriority;

	TWeakObjectPtr<UInputComponent> InputComponentRef;
	
public:	
	// Sets default values for this component's properties
	UIMCActorComponent();

	void BindMappingContext();
	
	void UnbindMappingContext();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void InitOwnerSubsystem();
	
	TWeakObjectPtr<UEnhancedInputLocalPlayerSubsystem> OwnerSubsystem;

	bool IsInputMappingBinding;

	virtual void InitializeComponent() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent);

	UInputComponent* GetInputComponentRef() const;

	UEnhancedInputComponent* GetEnhancedInputComponentRef() const;
};
