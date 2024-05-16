// Fill out your copyright notice in the Description page of Project Settings.


#include "InteractionHintCollision.h"

#include "..\..\Character\PlayerCharacter.h"
#include "RPG/ActorComponents/ScreenComponent.h"
#include "RPG/Interfaces/Interactable.h"
#include "RPG/UserWidgets/Hint/InteractableHintWidget.h"
#include "RPG/UserWidgets/Hint/InteractableHintBoxWidget.h"
#include "RPG/UserWidgets/HUD/ScreenWidget.h"
#include "Components/SphereComponent.h"
#include "RPG/ActorComponents/UIComponent/UIComponent.h"


// Sets default values for this component's properties
UInteractionHintCollision::UInteractionHintCollision()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	UE_LOG( LogTemp, Log, TEXT("UInteractionHintCollision"));
}


// Called when the game starts
void UInteractionHintCollision::BeginPlay()
{
	Super::BeginPlay();

	if( APlayerCharacter* Character = Cast<APlayerCharacter>( GetOwner() ) )
	{
		if( UUIComponent* UIComponent = Character->GetUIScreen() )
		{
			if( UScreenWidget* ScreenWidget = Cast<UScreenWidget>( UIComponent->GetWidgetPtr() ) )
			{
				InteractableHintBoxWidgetPtr = Cast<UInteractableHintBoxWidget>(ScreenWidget->GetHintBox());
			}
		}
	}
}

void UInteractionHintCollision::OnCollisionBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCollisionBegin_Implementation(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,
	                                       SweepResult);

	if( !Cast<APlayerCharacter>(GetOwner())->IsLocallyControlled() ) return;
	if( !InteractableHintBoxWidgetPtr.IsValid()) return;
	if( IInteractable* InteractableActor = Cast<IInteractable>(OtherActor))
	{
		for( FInteraction& Interaction : InteractableActor->GetInteractions() )
		{
			UInteractableHintWidget* InteractableHintWidget = Cast<UInteractableHintWidget>(InteractableHintBoxWidgetPtr->Add());
			InteractableHintWidget->SetInteraction( Interaction );
			FInteractableActorRecord& Record = InteractableActorBelongingHintWidget.FindOrAdd(OtherActor);
			Record.HintWidgets.Add( InteractableHintWidget );
		}
	}
}

void UInteractionHintCollision::OnCollisionEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnCollisionEnd_Implementation(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);

	if( !Cast<APlayerCharacter>(GetOwner())->IsLocallyControlled() ) return;
	if( !InteractableHintBoxWidgetPtr.IsValid()) return;
	if( IInteractable* InteractableActor = Cast<IInteractable>(OtherActor))
	{
		if( !InteractableActorBelongingHintWidget.Contains(OtherActor) ) return;
		for( UHintWidget* HintWidget : InteractableActorBelongingHintWidget[OtherActor].HintWidgets )
		{
			HintWidget->RemoveFromParent();
		}
		InteractableActorBelongingHintWidget.Remove(OtherActor);
	}
}


// Called every frame
void UInteractionHintCollision::TickComponent(float DeltaTime, ELevelTick TickType,
                                              FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

