// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPG/Actor/ItemBase.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "RPG/UserWidgets/DraggableSlotSocketWidget.h"
#include "RPG/UserWidgets/SlotSocketWidget.h"
#include "EquipmentSlotSocketWidget.generated.h"

class UEquipmentActorComponent;
class UEquipmentSlotSocketWidget;
class UButton;
class AItemBase;
enum class EEquipmentType : uint8;

DECLARE_DELEGATE_OneParam(FUpdateEquipmentSelectionBoxDelegate, UEquipmentSlotSocketWidget* );
DECLARE_DELEGATE_OneParam(FPrepareEquipmentDelegate, AItemBase* );
UCLASS()
class RPG_API UEquipmentSlotSocketWidget : public UDraggableSlotSocketWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	EEquipmentType BodySocket;

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	TObjectPtr<UClass> FilterItemClass = AItemBase::StaticClass();

public:
	TArray<TSharedRef<FInventoryItem>> GetFilteredItems();

	virtual bool FilterPass( const FInventoryItem& InventorySlot );

	TArray<TSharedRef<FInventoryItem>> GetSortedFilteredItems();

	void SortedByName(TArray<TSharedRef<FInventoryItem>>& Items);

	const EEquipmentType& GetBodySocket() const;

	void SetBodySocket(const EEquipmentType& Type);

	void SetFilterItemClass( UClass* ClassType );
	
	FUpdateEquipmentSelectionBoxDelegate UpdateEquipmentSelectionBoxDelegate;

	FPrepareEquipmentDelegate PrepareEquipmentDelegate;
	
	UFUNCTION()
	void ShowFilteredEquipmentSelectionBox();

	UFUNCTION()
	void Equip();

	virtual bool NativeOnDrop(const FGeometry& InGeometry, const FDragDropEvent& InDragDropEvent, UDragDropOperation* InOperation) override;

	virtual void NativeOnDragDetected(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent, UDragDropOperation*& OutOperation) override;

	virtual FReply NativeOnMouseButtonUp(const FGeometry& InGeometry, const FPointerEvent& InMouseEvent) override;

	virtual void Refresh() override;
};
