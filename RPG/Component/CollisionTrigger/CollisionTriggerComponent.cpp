// Fill out your copyright notice in the Description page of Project Settings.


#include "CollisionTriggerComponent.h"

#include "Components/SphereComponent.h"
#include "..\..\Character\PlayerCharacter.h"


// Sets default values for this component's properties
UCollisionTriggerComponent::UCollisionTriggerComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	bWantsInitializeComponent = true;

	OnComponentBeginOverlap.AddDynamic( this, &UCollisionTriggerComponent::OnCollisionBegin );
	OnComponentEndOverlap.AddDynamic( this, &UCollisionTriggerComponent::OnCollisionEnd );
	
}


// Called when the game starts
void UCollisionTriggerComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UCollisionTriggerComponent::InitializeComponent()
{
	Super::InitializeComponent();
	SetCollisionProfileName( "CollisionTrigger" );
}


	// Called every frame
	void UCollisionTriggerComponent::TickComponent(float DeltaTime, ELevelTick TickType,
												   FActorComponentTickFunction* ThisTickFunction)
	{
		Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UCollisionTriggerComponent::OnCollisionEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	
}

void UCollisionTriggerComponent::OnCollisionBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	
}
