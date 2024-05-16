// Fill out your copyright notice in the Description page of Project Settings.


#include "ShowEnemyUICollision.h"

#include "Components/WidgetComponent.h"
#include "RPG/Character/Enemy.h"


// Sets default values for this component's properties
UShowEnemyUICollision::UShowEnemyUICollision()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UShowEnemyUICollision::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UShowEnemyUICollision::OnCollisionBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	Super::OnCollisionBegin_Implementation(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex, bFromSweep,
	                                       SweepResult);
	if( AEnemy* Enemy = Cast<AEnemy>(OtherActor))
	{
		if( UWidgetComponent* HealthWidgetComponent = Enemy->GetInfoWidgetComponent() )
		{
			HealthWidgetComponent->SetVisibility( true );
			
		}
	} 
}

void UShowEnemyUICollision::OnCollisionEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	Super::OnCollisionEnd_Implementation(OverlappedComp, OtherActor, OtherComp, OtherBodyIndex);
	if( AEnemy* Enemy = Cast<AEnemy>(OtherActor))
	{
		if( UWidgetComponent* HealthWidgetComponent = Enemy->GetInfoWidgetComponent() )
		{
			HealthWidgetComponent->SetVisibility( false );
		}
	} 
}


// Called every frame
void UShowEnemyUICollision::TickComponent(float DeltaTime, ELevelTick TickType,
                                          FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

