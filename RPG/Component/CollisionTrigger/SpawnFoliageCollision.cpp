// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnFoliageCollision.h"

#include "RPG/Actor/Foliage/FoliageActor.h"
#include "RPG/ActorComponents/FISMC/SpawnFISMC.h"

// Sets default values for this component's properties
USpawnFoliageCollision::USpawnFoliageCollision()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

}


// Called when the game starts
void USpawnFoliageCollision::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void USpawnFoliageCollision::OnCollisionBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
                                                    UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if( USpawnFISMC* Foliage = Cast<USpawnFISMC>(OtherComp) )
	{
		if( Foliage->IsCollisionSpawnable() )
		{
			ReplaceFoliageToActor( Foliage, OtherBodyIndex )->GetInsideCollision().Emplace( OverlappedComp );
		}
	}
}

void USpawnFoliageCollision::OnCollisionEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor,
	UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	if( AFoliageActor* Actor = Cast<AFoliageActor>( OtherActor ) )
	{
		Actor->GetInsideCollision().Remove(OverlappedComp);
		if( Actor->GetInsideCollision().Num() == 0 )
		{
			ReplaceActorToFoliage( Actor );
		}
	}
}

AFoliageActor* USpawnFoliageCollision::ReplaceFoliageToActor(USpawnFISMC* Foliage, int32 Index)
{
		if( Foliage && Foliage->GetFoliageActor() )
		{
			UE_LOG( LogTemp, Log, TEXT("Replace foliage to actor"));
			FTransform InstanceTransform;
			Foliage->GetInstanceTransform( Index, InstanceTransform, true);
			AFoliageActor* Actor = Foliage->GetWorld()->SpawnActor<AFoliageActor>( Foliage->GetFoliageActor(), InstanceTransform );
			Actor->SetFoliageRef( Foliage );
			Actor->GetStaticMeshComponent()->SetStaticMesh( Foliage->GetStaticMesh() );
			Foliage->RemoveInstance( Index );
			return Actor;
		}
		return nullptr;
}

int32 USpawnFoliageCollision::ReplaceActorToFoliage(AFoliageActor* Actor)
{
	if( Actor && Actor->GetFoliageRef() && !Actor->IsActorBeingDestroyed() )
	{
		UE_LOG( LogTemp, Log, TEXT("Replace actor to foliage"));
		int32 Res = Actor->GetFoliageRef()->AddInstance( Actor->GetTransform(), true);
		Actor->Destroy();
		return Res;
	}
	return -1;
}


// Called every frame
void USpawnFoliageCollision::TickComponent(float DeltaTime, ELevelTick TickType,
                                                 FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

