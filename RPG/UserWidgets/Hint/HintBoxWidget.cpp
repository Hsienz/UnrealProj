// Fill out your copyright notice in the Description page of Project Settings.


#include "HintBoxWidget.h"

#include "HintWidget.h"
#include "InputActionValue.h"
#include "RPG/Interfaces/Interactable.h"
#include "Components/VerticalBox.h"

UHintWidget* UHintBoxWidget::Add()
{
	UHintWidget* HintWidget = CreateWidget<UHintWidget>(this, HintWidgetClass.Get() );
	HintBox->AddChildToVerticalBox( HintWidget );
	return HintWidget;
}

UVerticalBox* UHintBoxWidget::GetHintBox() const
{
	return HintBox;
}

void UHintBoxWidget::ClearChildren()
{
	HintBox->ClearChildren();
}


