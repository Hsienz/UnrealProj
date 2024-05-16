// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPG/UserWidgets/Hint/InteractableHintWidget.h"
#include "DialogueOption.generated.h"

/**
 * 
 */
DECLARE_DELEGATE_OneParam( FSelectOption, int32 );

UCLASS()
class RPG_API UDialogueOption : public UInteractableHintWidget
{
	GENERATED_BODY()

	int32 OptionIndex;
protected:
	virtual void NativeConstruct() override;

public:
	UFUNCTION()
	void SelectOption(AController* Instigator, AActor* Causer);

	void SetOptionIndex(int32 Index);
	
	FSelectOption SelectOptionDelegate;
};
