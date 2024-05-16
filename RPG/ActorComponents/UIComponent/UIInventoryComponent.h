// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "UIComponent.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "RPG/UserWidgets/DraggableSlotSocketWidget.h"
#include "UIInventoryComponent.generated.h"


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UUIInventoryComponent : public UUIComponent
{
	GENERATED_BODY()

	FInventorySharedPtr InventoryRef; 
public:
	// Sets default values for this component's properties
	UUIInventoryComponent();

	virtual bool UpdateUI() override;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;
	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
