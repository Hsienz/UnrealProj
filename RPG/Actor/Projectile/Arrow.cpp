// Fill out your copyright notice in the Description page of Project Settings.


#include "Arrow.h"

#include "Components/ArrowComponent.h"
#include "Components/CapsuleComponent.h"
#include "Components/SphereComponent.h"
#include "RPG/Actor/Shield.h"


// Sets default values
AArrow::AArrow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AArrow::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AArrow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AArrow::TraceOnShield_Implementation(AShield* Shield)
{
	Super::TraceOnShield_Implementation(Shield);
	FAttachmentTransformRules Rules(FAttachmentTransformRules::KeepWorldTransform);
	SetActorEnableCollision( false);
	AttachToActor( Shield, Rules );
}



