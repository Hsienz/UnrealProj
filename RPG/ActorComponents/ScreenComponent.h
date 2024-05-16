// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IMCActorComponent.h"
#include "ScreenComponent.generated.h"


class UUIComponent;
class UInputAction;
class UScreenWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UScreenComponent : public UIMCActorComponent
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UInputAction* ScrollHoldingItemSlotAction;

	TWeakObjectPtr<UUIComponent> UI;
public:
	// Sets default values for this component's properties
	UScreenComponent();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	virtual void InitializeComponent() override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};

