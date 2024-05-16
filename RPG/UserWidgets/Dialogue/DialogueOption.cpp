// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueOption.h"

void UDialogueOption::NativeConstruct()
{
	Super::NativeConstruct();
	Interaction.InteractionDelegate.BindDynamic( this, &UDialogueOption::SelectOption );
}

void UDialogueOption::SelectOption(AController* Instigator, AActor* Causer)
{
	SelectOptionDelegate.ExecuteIfBound(OptionIndex);
}

void UDialogueOption::SetOptionIndex(int32 Index)
{
	OptionIndex = Index;
}
