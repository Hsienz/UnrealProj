// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionSystem.h"
#include "RPG/Component/CollisionTrigger/SpawnFoliageCollision.h"
#include "EnhancedInputComponent.h"
#include "ScreenComponent.h"
#include "Camera/CameraComponent.h"
#include "FISMC/SpawnFISMC.h"
#include "RPG/Actor/Projectile/Arrow.h"
#include "..\Character\PlayerCharacter.h"
#include "RPG/Interfaces/Interactable.h"
#include "RPG/UserWidgets/Hint/InteractableHintBoxWidget.h"
#include "RPG/UserWidgets/HUD/ScreenWidget.h"
#include "RPG/ActorComponents/UIComponent/UIComponent.h"


// Sets default values for this component's properties
UInteractionSystem::UInteractionSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	// ...
}


void UInteractionSystem::HandleInteraction()
{
	if( InteractableHintBoxWidgetPtr.IsValid() )
	{
		InteractableHintBoxWidgetPtr->ProvokeSelection();
	}
}

void UInteractionSystem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if( UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent) )
	{
		EnhancedInputComponent->BindAction( InteractionAction, ETriggerEvent::Started, this, &UInteractionSystem::HandleInteraction );
	}
}

// Called when the game starts
void UInteractionSystem::BeginPlay()
{
	Super::BeginPlay();

	if( APlayerCharacter* Character = Cast<APlayerCharacter>( GetOwner() ) )
	{
		if( UUIComponent* UIComponent = Character->GetUIScreen() )
		{
			if( UScreenWidget* ScreenWidget = Cast<UScreenWidget>( UIComponent->GetWidgetPtr() ) )
			{
				InteractableHintBoxWidgetPtr = Cast<UInteractableHintBoxWidget>( ScreenWidget->GetHintBox() );
			}
		}
	}
	
}

void UInteractionSystem::FrontTrace()
{
	if( APlayerCharacter* Character = Cast<APlayerCharacter>(GetOwner()) )
	{
		UCameraComponent* Camera = Character->GetFollowCamera();
		if( !Camera ) UE_LOG( LogTemp, Warning, TEXT("%s dont have camera component"), *GetOwner()->GetName() );
		FVector StartPos = Camera->GetComponentLocation();
		FVector EndPos = StartPos + Camera->GetForwardVector() * Character->GetReachDistance();
		FCollisionQueryParams CollisionQueryParams;
		CollisionQueryParams.AddIgnoredActor( Character );
		bIsHit = GetWorld()->LineTraceSingleByChannel( HitResult, StartPos, EndPos, ECC_WorldStatic, CollisionQueryParams );
	}
}


// Called every frame
void UInteractionSystem::TickComponent(float DeltaTime, ELevelTick TickType,
                                       FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

