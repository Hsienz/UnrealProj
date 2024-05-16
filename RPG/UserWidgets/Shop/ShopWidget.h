// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ShopWidget.generated.h"

class USellingItemWidget;
struct FInventoryItem;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class RPG_API UShopWidget : public UUserWidget
{
	GENERATED_BODY()

protected:
	
	UPROPERTY(meta=(BindWidget))
	UVerticalBox* SellingItemBox;

	TSubclassOf<USellingItemWidget> BP_SellingItemWidget;

	
public:
	UVerticalBox* GetShopItemBox() const;

	void RemoveAllSellingItemFromBox();

	void AddSellingItemToBox(FInventoryItem& SellingItem);
};
