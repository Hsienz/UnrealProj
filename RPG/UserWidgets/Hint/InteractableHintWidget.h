// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "HintWidget.h"
#include "RPG/Interfaces/Interactable.h"
#include "InteractableHintWidget.generated.h"

class UButton;
struct FInteraction;
/**
 * 
 */
UCLASS()
class RPG_API UInteractableHintWidget : public UHintWidget
{
	GENERATED_BODY()
	IInteractable* InteractableActorRef;

protected:
	FInteraction Interaction;
	
	UPROPERTY(meta=(BindWidgetOptional))
	UButton* Button;
	
	virtual void NativeConstruct() override;
public:
	IInteractable* GetInteractableActor() const;
	
	void SetInteractableActor(IInteractable* InteractableActor);

	void SetInteraction(FInteraction& NewInteraction);

	const FInteraction& GetInteraction() const;
	
	void Select();

	void Unselect();

	void Interact(AController* EventInstigator, AActor* Causer);

	virtual void SetHintText(FText Text) override;
	
	UFUNCTION()
	void TriggerInteraction();
};
