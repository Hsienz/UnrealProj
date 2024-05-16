// Fill out your copyright notice in the Description page of Project Settings.


#include "NPC.h"


// Sets default values
ANPC::ANPC()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
/*
	FInteraction NewInteraction;
	NewInteraction = FInteraction(
		"Talk",
		FInteractionDelegate::CreateUObject(this, &ANPC::InteractionTalk)
	);
	Interactions.Add(NewInteraction);

	NewInteraction = FInteraction(
	"Buy",
		FInteractionDelegate::CreateUObject(this,&ANPC::InteractionBuy)
	);
	Interactions.Add(NewInteraction);
*/	
}

// Called when the game starts or when spawned
void ANPC::BeginPlay()
{
	Super::BeginPlay();
	
}

TArray<FInteraction>& ANPC::GetInteractions()
{
	return Interactions;
}

// Called every frame
void ANPC::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ANPC::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

