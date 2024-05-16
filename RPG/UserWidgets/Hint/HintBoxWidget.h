// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HintBoxWidget.generated.h"

struct FInputActionValue;
class UHintWidget;
class UVerticalBox;
/**
 * 
 */
UCLASS()
class RPG_API UHintBoxWidget : public UUserWidget
{
	GENERATED_BODY()
protected:
	UPROPERTY( meta=(BindWidget))
	UVerticalBox* HintBox;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	TSubclassOf<UHintWidget> HintWidgetClass;

	
public:
	virtual UHintWidget* Add();

	UVerticalBox* GetHintBox() const;

	void ClearChildren();
};
