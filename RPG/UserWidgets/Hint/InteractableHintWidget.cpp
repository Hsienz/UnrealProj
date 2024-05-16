// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractableHintWidget.h"

#include "Components/Button.h"
#include "RPG/Interfaces/Interactable.h"

void UInteractableHintWidget::NativeConstruct()
{
	Super::NativeConstruct();
	if( Button ) Button->OnClicked.AddDynamic(this, &UInteractableHintWidget::TriggerInteraction );
}

IInteractable* UInteractableHintWidget::GetInteractableActor() const
{
	return InteractableActorRef;
}

void UInteractableHintWidget::SetInteractableActor(IInteractable* InteractableActor)
{
	InteractableActorRef = InteractableActor;
}

void UInteractableHintWidget::SetInteraction(FInteraction& NewInteraction)
{
	this->Interaction = NewInteraction;
	SetHintText( NewInteraction.InteractionName );
}

const FInteraction& UInteractableHintWidget::GetInteraction() const
{
	return Interaction;
}


void UInteractableHintWidget::Select()
{
}

void UInteractableHintWidget::Unselect()
{
}

void UInteractableHintWidget::Interact(AController* EventInstigator, AActor* Causer)
{
	Interaction.InteractionDelegate.ExecuteIfBound(EventInstigator, Causer);
}

void UInteractableHintWidget::SetHintText(FText Text)
{
	Super::SetHintText(Text);
	Interaction.InteractionName = Text;
}

void UInteractableHintWidget::TriggerInteraction()
{
	Interaction.InteractionDelegate.ExecuteIfBound( GetOwningPlayerPawn()->GetInstigatorController(), GetOwningPlayerPawn() );
}
