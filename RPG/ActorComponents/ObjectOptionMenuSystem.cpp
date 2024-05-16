// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectOptionMenuSystem.h"

#include "EnhancedInputComponent.h"
#include "ObjectOptionMenu.h"
#include "RPG/Interfaces/HasObjectOptionMenu.h"
#include "Camera/CameraComponent.h"
#include "..\Character\PlayerCharacter.h"

// Sets default values for this component's properties
UObjectOptionMenuSystem::UObjectOptionMenuSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UObjectOptionMenuSystem::AttemptOpenObjectOptionMenu()
{
	APlayerCharacter* Character = Cast<APlayerCharacter>( GetOwner() );
	UCameraComponent* Camera = Character->GetFollowCamera();
	FVector StartPos = Camera->GetComponentLocation();
	FVector EndPos = StartPos + Camera->GetForwardVector() * 500;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor( Character );
	FHitResult HitResult;
	bool IsHit = GetWorld()->LineTraceSingleByChannel(HitResult, StartPos, EndPos, ECollisionChannel::ECC_WorldStatic, CollisionQueryParams );
	if( IsHit )
	{
		if( IHasObjectOptionMenu* ObjectOptionMenu  = Cast<IHasObjectOptionMenu>(HitResult.GetActor()) )
		{
			LastestOpenMenu = ObjectOptionMenu->GetOptionMenuComponent();
			LastestOpenMenu->OpenMenu();
			BindMappingContext();
		}
	}
}

void UObjectOptionMenuSystem::CloseObjectOptionMenu()
{
	if( LastestOpenMenu.IsValid() )
	{
		LastestOpenMenu->CloseMenu();
		// LastestOpenMenu = nullptr;
	}
	UnbindMappingContext();
}

void UObjectOptionMenuSystem::ToggleObjectOptionMenu()
{
	if( LastestOpenMenu.IsValid() ) CloseObjectOptionMenu();
	else AttemptOpenObjectOptionMenu();
}

void UObjectOptionMenuSystem::ClickMenuButton()
{
	if( LastestOpenMenu.IsValid() )
	{
		LastestOpenMenu->ClickMenuButton();
		CloseObjectOptionMenu();
	}
}


// Called when the game starts
void UObjectOptionMenuSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UObjectOptionMenuSystem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if( UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent) )
	{
		EnhancedInputComponent->BindAction( OpenObjectOptionMenuAction, ETriggerEvent::Started, this, &UObjectOptionMenuSystem::AttemptOpenObjectOptionMenu );
		EnhancedInputComponent->BindAction( CloseObjectOptionMenuAction, ETriggerEvent::Started, this, &UObjectOptionMenuSystem::CloseObjectOptionMenu );
		EnhancedInputComponent->BindAction( ClickOnMenuButtonAction, ETriggerEvent::Started, this, &UObjectOptionMenuSystem::ClickMenuButton );
	}
}


// Called every frame
void UObjectOptionMenuSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

