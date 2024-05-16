// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "SellingItemWidget.generated.h"

class UImage;
class UTextBlock;
struct FInventoryItem;
/**
 * 
 */
UCLASS()
class RPG_API USellingItemWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	FInventoryItem* SellingItem;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemNameText;

	UPROPERTY(meta=(BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* RemainingAmount;
	
public:

	void SetSellingItem( FInventoryItem& SellingItemSlot );

	FInventoryItem* GetSellingItem() const;
};
