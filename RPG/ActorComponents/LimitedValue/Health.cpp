// Fill out your copyright notice in the Description page of Project Settings.


#include "Health.h"

#include "RPG/Interfaces/Damageable.h"
#include "RPG/Interfaces/DamageableActor.h"


// Sets default values for this component's properties
UHealth::UHealth()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}

void UHealth::EventTriggerOnEmpty()
{
	Super::EventTriggerOnEmpty();
	if( IDamageable* DamageableActor = Cast<IDamageable>(GetOwner()) )
	{
		DamageableActor->Execute_HandleDead(GetOwner());
	}
}


// Called when the game starts
void UHealth::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UHealth::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

