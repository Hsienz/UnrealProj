// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPG/UserWidgets/DraggableSlotSocketWidget.h"

#include "HoldingItemSlotSocketWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UHoldingItemSlotSocketWidget : public UDraggableSlotSocketWidget
{
	GENERATED_BODY()

	UPROPERTY( meta=(BindWidget))
	UBorder* Border;
	
	FLinearColor OriginColor;

	UPROPERTY( EditAnywhere, BlueprintReadWrite, meta=( AllowPrivateAccess ) )
	FColor SelectColor;
public:
	virtual void NativeConstruct() override;
	void HandleOnSelect();
	void HandleOnUnselect();
	void AttachToComponent();
};
