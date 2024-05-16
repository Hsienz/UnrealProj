// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "SlotSocketWidget.generated.h"

class UContentWidget;
class UItemSlotWidget;
class UScaleBox;

UCLASS()
class RPG_API USlotSocketWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	
	UPROPERTY( meta=(BindWidget ))
	UScaleBox* SlotWidgetToUpdate;

public:
	UContentWidget* GetContentWidget() const;

	UItemSlotWidget* GetItemSlot() const ;

};
