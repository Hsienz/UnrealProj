// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "DlgSystem/DlgContext.h"
#include "DialogueBox.generated.h"

class UDlgContext;
class UInteractableHintBoxWidget;
class UTextBlock;
/**
 * 
 */
UCLASS()
class RPG_API UDialogueBox : public UUserWidget
{
	GENERATED_BODY()

protected:
	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UTextBlock* DialogueText;

	UPROPERTY(BlueprintReadOnly,meta=(BindWidget))
	UInteractableHintBoxWidget* DialogueOptionsBox;

	void UpdateDialogueOptions();

	TWeakObjectPtr<UDlgContext> Context;
	
public:
	UFUNCTION(BlueprintCallable)
	void StartDialogue(UDlgDialogue* DlgDialogue, const TArray<UObject*>& Participants);

	UFUNCTION(BlueprintCallable)
	void StartDialogueWithDefaultParticipants( UDlgDialogue* DlgDialogue );
	
	UFUNCTION(BlueprintCallable)
	void UpdateDialogue();

	UFUNCTION(BlueprintCallable)
	void SelectDialogueOption( int32 Index );

	bool CanProcessByKey() const;

	void EndDialogue();
};
