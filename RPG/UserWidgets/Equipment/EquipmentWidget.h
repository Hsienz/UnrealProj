// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "RPG/UserWidgets/DraggableSlotSocketWidget.h"
#include "EquipmentWidget.generated.h"

class UEquipmentSelectionBoxWidget;
struct FInventoryItem;
class UInteractableHintBoxWidget;
class UEquipmentSlotSocketWidget;
/**
 * 
 */


UCLASS()
class RPG_API UEquipmentWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY(meta=(BindWidget))
	UEquipmentSlotSocketWidget* LeftHandSocketWidget;
	
	UPROPERTY(meta=(BindWidget))
	UEquipmentSlotSocketWidget* RightHandSocketWidget;

	UPROPERTY(meta=(BindWidget))
	UEquipmentSelectionBoxWidget* EquipmentBox;
	
	virtual bool Initialize() override;

	virtual void NativeConstruct() override;

	UFUNCTION()
	virtual void HandleOnEquipmentSelectionWidgetClick();

	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;
public:
	UFUNCTION()
	void UpdateEquipmentSelectionBox(UEquipmentSlotSocketWidget* SocketWidget);
};
