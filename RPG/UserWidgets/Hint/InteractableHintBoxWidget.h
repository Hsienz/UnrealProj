// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HintBoxWidget.h"
#include "InteractableHintBoxWidget.generated.h"

class UInteractableHintWidget;
/**
 * 
 */
UCLASS()
class RPG_API UInteractableHintBoxWidget : public UHintBoxWidget
{
	GENERATED_BODY()
	
	int32 SelectedIndex;

public:
	void ProvokeSelection();
	
	void ClampSelectedIndex();

	void Scroll(const FInputActionValue& Value);

	virtual UHintWidget* Add() override;
	
	// Unselect element on SelectedIndex, Select NewIndex, and update NewIndex to UpdateIndex
	void SetSelectedIndex(int32 NewIndex);
};
