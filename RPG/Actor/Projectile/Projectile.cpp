// Fill out your copyright notice in the Description page of Project Settings.


#include "Projectile.h"

#include "Components/ArrowComponent.h"
#include "GameFramework/ProjectileMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "RPG/Character/PlayerCharacter.h"


// Sets default values
AProjectile::AProjectile()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	ProjectileMovementComponent = CreateDefaultSubobject<UProjectileMovementComponent>(TEXT("ProjectileMovementComponent"));
	ProjectileMovementComponent->bAutoActivate = false;
	ProjectileMovementComponent->UpdatedComponent = StaticMesh;
	StaticMesh->SetCollisionProfileName( "NoCollision" );

	TraceCenter = CreateDefaultSubobject<UArrowComponent>(TEXT("TipArrow"));
	TraceCenter->SetupAttachment( StaticMesh );
	
}


// Called when the game starts or when spawned
void AProjectile::BeginPlay()
{
	Super::BeginPlay();
	PrevPosition = TraceCenter->GetComponentLocation();
}



void AProjectile::ProjectileHit( const FHitResult& Target )
{
	// StaticMesh->SetCollisionProfileName("IgnoreOnlyPawn");
	TryApplyDamageToTarget( Target.GetActor() );
	StopDamageTrace();
}


void AProjectile::Launch()
{
	if( ProjectileMovementComponent )
	{
		StaticMesh->SetCollisionProfileName( "Projectile");
		ProjectileMovementComponent->Velocity = ( GetActorForwardVector() * ProjectileMovementComponent->InitialSpeed );
		ProjectileMovementComponent->Activate();
		StartDamageTrace();
		NatualDestroy();
		bLaunched = true;
	}
}

void AProjectile::NatualDestroy()
{
	if( DestroyAfterSec )
	{
		GetWorldTimerManager().SetTimer(DestroyTimerHandle, FTimerDelegate::CreateLambda([&](){Destroy();}), DestroyAfterSec, false );
	}
	else
	{
		Destroy();
	}
}

void AProjectile::SetCharacterRef(ACharacter* Character )
{
	Super::SetCharacterRef(Character);
	if( Character )
	{
		StaticMesh->IgnoreActorWhenMoving( Character, true );
	}
}

void AProjectile::DamageTrace_Implementation()
{
	Super::DamageTrace_Implementation();
	FHitResult HitResult;
	FVector EndLocation = TraceCenter->GetComponentLocation();
	if( UKismetSystemLibrary::SphereTraceSingleByProfile(
		GetWorld(),
		PrevPosition,
		EndLocation,
		5,
		ProjectileProfileName,
		false,
		{GetCharacterRef()},
		EDrawDebugTrace::ForDuration,
		HitResult,
		true)
		)
	{
		bIsHit = true;
		ProjectileHit(HitResult);
	}
	PrevPosition = EndLocation;
	
}

// Called every frame
void AProjectile::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

