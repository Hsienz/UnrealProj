// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "DraggableSlotSocketWidget.h"
#include "Blueprint/UserWidget.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "InventoryMenu.generated.h"

class UUniformGridPanel;
class UInventorySystem;
class UGridPanel;
/**
 * 
 */
UCLASS()
class RPG_API UInventoryMenu : public UUserWidget
{
	GENERATED_BODY()

	// TWeakObjectPtr<UInventorySystem> InventorySystem;
	FInventorySharedPtr InventoryRef;
	/*
	UPROPERTY(BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess))
	TSubclassOf<UInventoryItemSlotWidget> InventoryItemSlotWidget;
*/
	UPROPERTY( meta=(BindWidget) )
	UUniformGridPanel* ItemSlotGrid;
public:

	virtual void NativeConstruct() override;

	void UpdateItemSlotGrid();
/*
	void SetInventorySystem( UInventorySystem* InventorySystem );

	UInventorySystem* GetInventorySystem() const;
*/
	int32 GetItemSlotNum();

	UUniformGridPanel* GetItemSlotGrid() const;

	void RemoveAllChild();

};
