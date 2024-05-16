// Fill out your copyright notice in the Description page of Project Settings.


#include "FoliageActor.h"

#include "RPG/ActorComponents/InventorySystem.h"
#include "RPG/ActorComponents/LimitedValue/Health.h"
#include "RPG/Interfaces/HasInventory.h"
#include "RPG/Struct/DropItem.h"
#include "GameFramework/Character.h"

// Sets default values
AFoliageActor::AFoliageActor()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	HealthComponent = CreateDefaultSubobject<UHealth>(TEXT("HealthComponent"));

	SetMobility( EComponentMobility::Movable );
	
	HealthComponent->SetValue( Max, 1);
	HealthComponent->SetValue( Current, 1);
}

UHealth* AFoliageActor::GetHealth_Implementation()
{
	return HealthComponent;
}

void AFoliageActor::HandleDead_Implementation()
{
	Destroy();
}

void AFoliageActor::SetFoliageRef(USpawnFISMC* Foliage)
{
	FoliageRef = Foliage;
	
}

USpawnFISMC* AFoliageActor::GetFoliageRef() const
{
	return FoliageRef;
}


// Called when the game starts or when spawned
void AFoliageActor::BeginPlay()
{
	Super::BeginPlay();
	
}

float AFoliageActor::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator,
	AActor* DamageCauser)
{
	HealthComponent->DecreaseCurrentValue( DamageAmount );
	if( UInventorySystem* Inventory = Cast<IHasInventory>( EventInstigator->GetCharacter() )->GetInventory() )
	{
		GetDropItem( Inventory );
	}
	return Super::TakeDamage(DamageAmount, DamageEvent, EventInstigator, DamageCauser);
}

void AFoliageActor::GetDropItem(UInventorySystem* Inventory)
{
	for( auto& x:DropItems )
	{
		Inventory->AddItem( x );
	}
}

// Called every frame
void AFoliageActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

TSet<TWeakObjectPtr<UPrimitiveComponent>>& AFoliageActor::GetInsideCollision()
{
	return InsideCollision;
}
