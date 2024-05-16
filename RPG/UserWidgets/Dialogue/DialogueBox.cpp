// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueBox.h"

#include "DialogueOption.h"
#include "Components/TextBlock.h"
#include "Components/VerticalBox.h"
#include "DlgSystem/DlgContext.h"
#include "DlgSystem/DlgManager.h"
#include "RPG/Interfaces/Interactable.h"
#include "RPG/UserWidgets/Hint/HintWidget.h"
#include "RPG/UserWidgets/Hint/InteractableHintBoxWidget.h"
#include "RPG/UserWidgets/Hint/InteractableHintWidget.h"

void UDialogueBox::UpdateDialogueOptions()
{
	if( !DialogueOptionsBox->GetHintBox() ) return;
	for( UWidget* WidgetRef : DialogueOptionsBox->GetHintBox()->GetAllChildren() ) WidgetRef->RemoveFromParent();
	int32 DialogueOptionIndex = 0;
	for( const FDlgEdge& Edge :Context->GetOptionsArray())
	{
		if( !Edge.GetText().IsEmpty() )
		{
			UDialogueOption* HintWidget = Cast<UDialogueOption>(DialogueOptionsBox->Add());
			HintWidget->SetHintText( Edge.GetText() );
			HintWidget->SetOptionIndex(DialogueOptionIndex++);
			HintWidget->SelectOptionDelegate.BindUObject( this, &UDialogueBox::SelectDialogueOption );
			UE_LOG( LogTemp, Warning, TEXT("%s"), *Edge.GetText().ToString() );
			
		}
	}
	if( DialogueOptionsBox->GetHintBox()->GetChildrenCount() ) DialogueOptionsBox->SetVisibility( ESlateVisibility::Visible );
	else DialogueOptionsBox->SetVisibility(ESlateVisibility::Hidden );
}

void UDialogueBox::StartDialogue(UDlgDialogue* DlgDialogue, const TArray<UObject*>& Participants)
{
	Context = UDlgManager::StartDialogue(DlgDialogue, Participants);
	SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer()->SetShowMouseCursor( true );
	UpdateDialogue();
}

void UDialogueBox::StartDialogueWithDefaultParticipants(UDlgDialogue* DlgDialogue)
{
	Context = UDlgManager::StartDialogueWithDefaultParticipants(GetWorld(), DlgDialogue);
	SetVisibility(ESlateVisibility::Visible);
	GetOwningPlayer()->SetShowMouseCursor( true );
	UpdateDialogue();
}



void UDialogueBox::UpdateDialogue()
{
	DialogueText->SetText( Context->GetActiveNodeText() );
	UpdateDialogueOptions();
}

void UDialogueBox::SelectDialogueOption(int32 Index)
{
	if( !Context.IsValid() ) return; 
	if( !Context->ChooseOption(Index) || Context->HasDialogueEnded() )
	{
		EndDialogue();
		return;
	}
	UpdateDialogue();
}


bool UDialogueBox::CanProcessByKey() const
{
	if( !DialogueOptionsBox || !DialogueOptionsBox->GetHintBox() ) return false;
	return DialogueOptionsBox->GetHintBox()->GetChildrenCount() == 0;
}

void UDialogueBox::EndDialogue()
{
	Context = nullptr;
	SetVisibility( ESlateVisibility::Hidden );
	GetOwningPlayer()->SetShowMouseCursor( false );
}
