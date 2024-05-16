// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPG/UserWidgets/Hint/InteractableHintBoxWidget.h"
#include "EquipmentSelectionBoxWidget.generated.h"

class UEquipmentSlotSocketWidget;
/**
 * 
 */
UCLASS()
class RPG_API UEquipmentSelectionBoxWidget : public UInteractableHintBoxWidget
{
	GENERATED_BODY()
	
	TWeakObjectPtr<UEquipmentSlotSocketWidget> Socket;
public:
	void SetSocket( UEquipmentSlotSocketWidget* NewSocket );
};
