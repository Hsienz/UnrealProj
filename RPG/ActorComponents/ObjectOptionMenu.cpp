// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectOptionMenu.h"

#include "RPG/UserWidgets/ObjectOptionMenuWidget.h"

// Sets default values for this component's properties
UObjectOptionMenu::UObjectOptionMenu()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}

void UObjectOptionMenu::OpenMenu()
{
	ObjectOptionMenuWidget = CreateWidget<UObjectOptionMenuWidget>( GetWorld()->GetFirstPlayerController() , Menu );
	if( ObjectOptionMenuWidget.IsValid() )
	{
		ObjectOptionMenuWidget->SetOwnerActor( GetOwner() );
		ObjectOptionMenuWidget->AddToViewport();
	}
	else {
		UE_LOG(LogTemp, Warning, TEXT("Widget is null"));
	}
}

void UObjectOptionMenu::CloseMenu()
{
	if( ObjectOptionMenuWidget.IsValid() ) {
		ObjectOptionMenuWidget->RemoveFromParent();
	}
}
/*
void UObjectOptionMenu::ToggleMenu()
{
	if( ObjectOptionMenuWidget.IsValid() ) CloseMenu();
	else OpenMenu();
}
*/

void UObjectOptionMenu::ClickMenuButton()
{
	if( ObjectOptionMenuWidget.IsValid() )
	{
		ObjectOptionMenuWidget->ClickActiveButton();
	}
}


// Called when the game starts
void UObjectOptionMenu::BeginPlay()
{
	Super::BeginPlay();

	// Menu = UObjectOptionMenuWidget::StaticClass();
	
}


// Called every frame
void UObjectOptionMenu::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

