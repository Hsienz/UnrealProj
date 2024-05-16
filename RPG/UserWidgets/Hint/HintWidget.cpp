// Fill out your copyright notice in the Description page of Project Settings.


#include "HintWidget.h"

#include "HintBoxWidget.h"
#include "RPG/Interfaces/Interactable.h"
#include "Components/Image.h"
#include "Components/TextBlock.h"


UUserWidget* UHintWidget::GetParentWidgetRef() const
{
	return ParentWidgetRef.Get();
}

void UHintWidget::SetParentWidgetRef(UUserWidget* ParentWidget)
{
	ParentWidgetRef = ParentWidget;
}

void UHintWidget::SetHintText(FText Text)
{
	HintText->SetText( Text );
}

void UHintWidget::SetHintIcon(UTexture2D* Texture)
{
	HintIcon->SetBrushFromTexture( Texture );
}
