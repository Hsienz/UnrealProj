// Fill out your copyright notice in the Description page of Project Settings.


#include "IMCActorComponent.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "GameFramework/Character.h"


// Sets default values for this component's properties
UIMCActorComponent::UIMCActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
}


// Called when the game starts
void UIMCActorComponent::BeginPlay()
{
	Super::BeginPlay();
	InitOwnerSubsystem();
}

void UIMCActorComponent::InitOwnerSubsystem()
{
	if( APlayerController* PlayerController = Cast<APlayerController>( Cast<ACharacter>(GetOwner())->Controller ) ) 
		OwnerSubsystem = ULocalPlayer::GetSubsystem<UEnhancedInputLocalPlayerSubsystem>(PlayerController->GetLocalPlayer());
}


void UIMCActorComponent::InitializeComponent()
{
	Super::InitializeComponent();
}

// Called every frame
void UIMCActorComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
}

void UIMCActorComponent::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
}

UInputComponent* UIMCActorComponent::GetInputComponentRef() const
{
	return InputComponentRef.IsValid() ? InputComponentRef.Get() : nullptr;
}

UEnhancedInputComponent* UIMCActorComponent::GetEnhancedInputComponentRef() const
{
	return Cast<UEnhancedInputComponent>(GetInputComponentRef());
}

void UIMCActorComponent::BindMappingContext()
{
	if( OwnerSubsystem.IsValid() )
	{
		OwnerSubsystem->AddMappingContext(InputMappingContext, InputMappingContextPriority);
		IsInputMappingBinding = true;
	}
}

void UIMCActorComponent::UnbindMappingContext()
{
	if( OwnerSubsystem.IsValid() )
	{
		OwnerSubsystem->RemoveMappingContext(InputMappingContext);
		IsInputMappingBinding = false;
	}
}

