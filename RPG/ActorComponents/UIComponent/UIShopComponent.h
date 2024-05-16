// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIComponent.h"
#include "UIShopComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UUIShopComponent : public UUIComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UUIShopComponent();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual bool UpdateUI() override;

	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
