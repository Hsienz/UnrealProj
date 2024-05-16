// Fill out your copyright notice in the Description page of Project Settings.


#include "ScreenComponent.h"

#include "EnhancedInputComponent.h"
#include "Blueprint/UserWidget.h"
#include "..\Character\PlayerCharacter.h"
#include "RPG/UserWidgets/HUD/ScreenWidget.h"
#include "UIComponent/UIComponent.h"


// Sets default values for this component's properties
UScreenComponent::UScreenComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
}

// Called when the game starts
void UScreenComponent::BeginPlay()
{
	Super::BeginPlay();
	
}

void UScreenComponent::InitializeComponent()
{
	Super::InitializeComponent();
	if( APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner()))
	{
		UI = Character->GetUIScreen();
		if( UI.IsValid() )
		{
			UI->CreateUI( true);
		}
	}
}

void UScreenComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if( UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent) )
	{
		if( UI.IsValid() && UI->GetWidgetPtr() && Cast<UScreenWidget>(UI->GetWidgetPtr()) ) {
			EnhancedInputComponent->BindAction( ScrollHoldingItemSlotAction, ETriggerEvent::Started, Cast<UScreenWidget>( UI->GetWidgetPtr() ), &UScreenWidget::Scroll );
		}
	}
}


// Called every frame
void UScreenComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

