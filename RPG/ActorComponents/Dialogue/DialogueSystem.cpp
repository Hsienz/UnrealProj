// Fill out your copyright notice in the Description page of Project Settings.


#include "DialogueSystem.h"

#include "EnhancedInputComponent.h"
#include "RPG/ActorComponents/ScreenComponent.h"
#include "RPG/ActorComponents/UIComponent/UIComponent.h"
#include "..\..\Character\PlayerCharacter.h"
#include "RPG/UserWidgets/Dialogue/DialogueBox.h"
#include "RPG/UserWidgets/HUD/ScreenWidget.h"


// Sets default values for this component's properties
UDialogueSystem::UDialogueSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}


// Called when the game starts
void UDialogueSystem::BeginPlay()
{
	Super::BeginPlay();
	if( APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner()))
	{
		if( UUIComponent* UIScreen = Character->GetUIScreen() )
		{
			if( UScreenWidget* ScreenWidget = Cast<UScreenWidget>(UIScreen->GetWidgetPtr() ) )
			{
				DialogueBoxRef = ScreenWidget->GetDialogueBox();
			}
		}
	}
	// ...
	
}

void UDialogueSystem::ToNextDialogue()
{
	if( DialogueBoxRef.IsValid())
	{
		if( DialogueBoxRef->CanProcessByKey() ) DialogueBoxRef->SelectDialogueOption(0);
	}
}


// Called every frame
void UDialogueSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UDialogueSystem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if( UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent) )
	{
		EnhancedInputComponent->BindAction( ToNextDialogueAction, ETriggerEvent::Started, this, &UDialogueSystem::ToNextDialogue);
	}
}

