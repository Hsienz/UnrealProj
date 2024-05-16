// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ScreenWidget.generated.h"


class UDialogueBox;
class UHintBoxWidget;
struct FInventoryItem;
class UItemPrimaryDataAsset;
class UDraggableSlotSocketWidget;
class UItemSlotWidget;
struct FInputActionValue;
class UHorizontalBox;
/**
 * 
 */
UCLASS()
class RPG_API UScreenWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	UHorizontalBox* HoldingItemBox;

	int32 CurrentHoldingItemIndex;

	UPROPERTY(meta=(BindWidget))
	UHintBoxWidget* HintBox;

	UPROPERTY(BlueprintReadOnly, meta=(BindWidget,AllowPrivateAccess))
	UDialogueBox* DialogueBox;

protected:
	virtual void NativeConstruct() override;

public:
	UHorizontalBox* GetHoldingItemBox() const;
	
	UItemPrimaryDataAsset* GetHoldingItemAsset() const;
	
	UItemSlotWidget* GetHoldingItemSlot() const;
	
	UDraggableSlotSocketWidget* GetHoldingItemSocket() const;

	TSharedPtr<FInventoryItem> GetHoldingInventorySlot() const;

	UHintBoxWidget* GetHintBox() const;

	UDialogueBox* GetDialogueBox() const;
	
	UFUNCTION()
	void Scroll( const FInputActionValue& Value );
	
};