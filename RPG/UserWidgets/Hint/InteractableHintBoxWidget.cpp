// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableHintBoxWidget.h"

#include "HintWidget.h"
#include "InputActionValue.h"
#include "InteractableHintWidget.h"
#include "RPG/Interfaces/Interactable.h"
#include "Components/VerticalBox.h"

void UInteractableHintBoxWidget::ProvokeSelection()
{
	if(SelectedIndex < HintBox->GetChildrenCount() )
	{
		if( UInteractableHintWidget* HintWidget = Cast<UInteractableHintWidget>(HintBox->GetChildAt( SelectedIndex )) )
		{
		HintWidget->Interact( GetOwningPlayer(), GetOwningPlayerPawn() );
			
		}
	}
}

void UInteractableHintBoxWidget::ClampSelectedIndex()
{
	int32 NewSelectedIndex = FMath::Clamp( SelectedIndex, 0, HintBox->GetChildrenCount()-1);
	SetSelectedIndex( NewSelectedIndex );
}

void UInteractableHintBoxWidget::Scroll(const FInputActionValue& Value)
{
	float WheelValue = Value.Get<float>();
	int NewSelectedIndex = SelectedIndex;
	if( WheelValue < 0.8 )
	{
		NewSelectedIndex--;
	}
	else if( WheelValue > 0.8 )
	{
		NewSelectedIndex++;
	}
	NewSelectedIndex = ( NewSelectedIndex + HintBox->GetChildrenCount() ) % HintBox->GetChildrenCount();

	SetSelectedIndex( NewSelectedIndex );
}

UHintWidget* UInteractableHintBoxWidget::Add()
{
	UHintWidget* Res = CreateWidget<UInteractableHintWidget>( this, HintWidgetClass.Get());
	HintBox->AddChildToVerticalBox( Res );
	return Res;
}

void UInteractableHintBoxWidget::SetSelectedIndex(int32 NewIndex)
{
	if( SelectedIndex == NewIndex ) return;
	if( SelectedIndex < HintBox->GetChildrenCount() )
	{
		if( UInteractableHintWidget* InteractableHintWidget = Cast<UInteractableHintWidget>(HintBox->GetChildAt(SelectedIndex)) )
		{
			InteractableHintWidget->Unselect();
		}
	}
	SelectedIndex = NewIndex;
	if( SelectedIndex < HintBox->GetChildrenCount() )
	{
		
		if( UInteractableHintWidget* InteractableHintWidget = Cast<UInteractableHintWidget>(HintBox->GetChildAt(SelectedIndex)) )
		{
			InteractableHintWidget->Select();
		}
	}
}
