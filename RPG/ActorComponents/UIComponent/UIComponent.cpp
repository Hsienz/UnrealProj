// Fill out your copyright notice in the Description page of Project Settings.


#include "UIComponent.h"

#include "Blueprint/UserWidget.h"
#include "..\..\Character\PlayerCharacter.h"
#include "RPG/UserWidgets/InventoryMenu.h"


// Sets default values for this component's properties
UUIComponent::UUIComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

UUserWidget* UUIComponent::GetWidgetPtr() const
{
	return WidgetPtr.IsValid() ? WidgetPtr.Get() : nullptr;
}

bool UUIComponent::CreateUI(bool InitShow)
{
	if( WidgetPtr.IsValid() ||  !BP_Widget ) return false;

	UE_LOG(LogTemp,Log,TEXT("\n%p\n%p\n%p\n%p\n%p"),
		GetWorld()->GetFirstPlayerController(),
		Cast<APlayerController>(GetOwner()->GetInstigator()),
		Cast<APlayerController>(Cast<APlayerCharacter>(GetOwner())->GetController()),
		GetOwner()->GetInstigator(),
		Cast<APlayerCharacter>(GetOwner())->GetController());
	
	WidgetPtr = CreateWidget( GetWorld()->GetFirstPlayerController(), BP_Widget.Get() );
	if( !WidgetPtr.IsValid() ) return false;
	WidgetPtr->AddToViewport();
	UpdateUI();
	if( !InitShow ) HideUI();
	return true;
}

void UUIComponent::ShowUI()
{
	UpdateUI();
	SetUIVisibility( ESlateVisibility::Visible );
	GetWidgetPtr()->GetOwningPlayer()->bShowMouseCursor = true;
	GetWidgetPtr()->GetOwningPlayer()->SetInputMode( FInputModeGameAndUI() );
	GetWidgetPtr()->GetOwningPlayer()->SetIgnoreLookInput( true );
	GetWidgetPtr()->GetOwningPlayer()->SetIgnoreMoveInput( true );
}

void UUIComponent::HideUI()
{
	SetUIVisibility( ESlateVisibility::Hidden );
	GetWidgetPtr()->GetOwningPlayer()->bShowMouseCursor = false;
	GetWidgetPtr()->GetOwningPlayer()->SetInputMode( FInputModeGameOnly() );
	GetWidgetPtr()->GetOwningPlayer()->SetIgnoreLookInput( false );
	GetWidgetPtr()->GetOwningPlayer()->SetIgnoreMoveInput( false );
}

bool UUIComponent::UpdateUI()
{
	return WidgetPtr.IsValid();
}

void UUIComponent::ToggleUI()
{
	if( WidgetPtr.IsValid() )
	{
		if( WidgetPtr->GetVisibility() != ESlateVisibility::Hidden )
		{
			HideUI();
		}
		else
		{
			ShowUI();
		}
	}
}

bool UUIComponent::DestroyUI()
{
	if( !WidgetPtr.IsValid() ) return false;
	WidgetPtr->RemoveFromParent();
	return true;
}

void UUIComponent::SetUIVisibility(ESlateVisibility Visibility)
{
	if( WidgetPtr.IsValid())
	{
		WidgetPtr->SetVisibility( Visibility );
	}
}


// Called when the game starts
void UUIComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UUIComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

