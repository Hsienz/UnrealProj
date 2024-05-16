// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DraggableSlotSocketWidget.h"
#include "Blueprint/UserWidget.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "ItemSlotWidget.generated.h"

class UDraggableSlotSocketWidget;
class UImage;
struct FInventoryItem;
class UTextBlock;
/**
 * 
 */
UCLASS()
class RPG_API UItemSlotWidget : public UUserWidget
{
	GENERATED_BODY()
	
	UPROPERTY(meta=(BindWidget))
	UImage* ItemIcon;
	
protected:
	UPROPERTY(meta=(BindWidget))
	UTextBlock* Amount;

	TSharedPtr<FInventoryItem> InventorySlotRef;

	TWeakObjectPtr<UDraggableSlotSocketWidget> SocketRef;

public:
	virtual void Update(UDraggableSlotSocketWidget* Socket, TSharedRef<FInventoryItem>& InventorySlot);

	TSharedPtr<FInventoryItem> GetInventorySlot() const;

	void SetInventorySlotRef(TSharedRef<FInventoryItem>& InventorySlot);

	UDraggableSlotSocketWidget* GetSocket();

	void SyncInventorySlotRefToUI();
	
};
