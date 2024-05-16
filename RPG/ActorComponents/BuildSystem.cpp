// Fill out your copyright notice in the Description page of Project Settings.


#include "BuildSystem.h"

#include "EnhancedInputComponent.h"
#include "EnhancedInputSubsystems.h"
#include "RPG/Actor/BuildingPart.h"
#include "RPG/Component/BuildSocket/SocketComponent.h"
#include "RPG/GameInstance/GlobalGameInstance.h"
#include "RPG/PrimaryDataAssets/BuildingPartPrimaryDataAsset.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "..\Character\PlayerCharacter.h"

// Sets default values for this component's properties
UBuildSystem::UBuildSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;
	UE_LOG( LogTemp, Warning, TEXT("UBuildingSystem::UBuindingSystem"));

}


void UBuildSystem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
	if( UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent) )
	{
		EnhancedInputComponent->BindAction( ToggleBuildModeInputAction, ETriggerEvent::Started, this, &UBuildSystem::ToggleBuildMode );

		EnhancedInputComponent->BindAction( BuildInputAction, ETriggerEvent::Started, this, &UBuildSystem::Build);

		EnhancedInputComponent->BindAction( RotateBuildPreviewInputAction, ETriggerEvent::Started, this, &UBuildSystem::RotateBuildPreview);
		EnhancedInputComponent->BindAction( RotateBuildPreviewInputAction, ETriggerEvent::Completed, this, &UBuildSystem::StopRotationBuildOPreview);

		EnhancedInputComponent->BindAction( SwitchHoldingBuildingPartPrimaryDataAssetInputAction, ETriggerEvent::Started, this,  &UBuildSystem::SwitchHoldingBuildingPartPrimaryDataAsset );
	}
}

USocketComponent* UBuildSystem::GetSnappableSocketComponent()
{
	for( FHitResult& HitResult : HitResults )
	{
		if( HitResult.GetComponent() )
		{
			if(  USocketComponent* SocketComponent = Cast<USocketComponent>( HitResult.Component ) )
			{
				if( SocketComponent->IsInSocketTypeFlags( GetCurrentHoldingBuildingPartPrimaryDataAsset()->GetBuildType() ) )
				{
					return SocketComponent;
				}
			}
		}
	}
	return nullptr;
}

void UBuildSystem::AttemptCreateBuildPreview()
{
			if( !BuildPreview.IsValid() )
			{
				BuildPreview = NewObject<UStaticMeshComponent>(GetOwner(),TEXT("BuildPreview"));
				AttemptUpdateBuildPreview();
				BuildPreview->SetCollisionEnabled(ECollisionEnabled::NoCollision);
				BuildPreview->SetupAttachment( GetOwner()->GetRootComponent() );
				BuildPreview->RegisterComponent();
			}
}

void UBuildSystem::AttemptDestroyBuildPreview()
{
	if( BuildPreview.IsValid() ) {
		BuildPreview->DestroyComponent();
	}
}

void UBuildSystem::UpdateHitResults()
{
	UCameraComponent* CameraComponent = Cast<APlayerCharacter>(GetOwner())->GetCamera();
	FVector StartPos = CameraComponent->GetComponentLocation();
	FVector ForwardDir = CameraComponent->GetForwardVector();
	FVector EndPos = StartPos + ForwardDir * BuildReachDistance;
	FCollisionQueryParams CollisionQueryParams;
	CollisionQueryParams.AddIgnoredActor( GetOwner() );  // ignore self
	bBuildLocationHit = GetWorld()->LineTraceMultiByChannel( HitResults, StartPos, EndPos, ECC_WorldStatic, CollisionQueryParams );
	DrawDebugLine(GetWorld(), StartPos, EndPos, FColor::Red, false, 5);
}

void UBuildSystem::RotateBuildPreview()
{
	if( BuildPreview.IsValid() ) {
		GetWorld()->GetTimerManager().SetTimer( RotatePreviewTimerHandle, [&]()
		{
			if( BuildPreview.IsValid() ) BuildPreview->AddWorldRotation( FRotator(0,10,0) );
		}, 0.1, true );
	}
}

void UBuildSystem::StopRotationBuildOPreview()
{
	if( RotatePreviewTimerHandle.IsValid() )
	{
		GetWorld()->GetTimerManager().ClearTimer( RotatePreviewTimerHandle);
	}
}


void UBuildSystem::ToggleBuildMode(const FInputActionValue& Value )
{
	BuildMode = !BuildMode;
	if(BuildMode)
	{
		BindMappingContext();
	}
	else
	{
		UnbindMappingContext();
		if( BuildPreview.IsValid() ) BuildPreview->DestroyComponent();
	}
}

void UBuildSystem::Build(const FInputActionValue& Value )
{
	if( BuildMode && BuildPreview.IsValid() )
	{
		UE_LOG( LogTemp, Log, TEXT("Build"));
		ABuildingPart* BuildingPart = GetWorld()->SpawnActor<ABuildingPart>(
			GetCurrentHoldingBuildingPartPrimaryDataAsset()->GetBuildingPartClass().Get(),
			BuildPreview->GetComponentLocation(),
			BuildPreview->GetComponentRotation()
			);
		BuildingPart->SetAsset( GetCurrentHoldingBuildingPartPrimaryDataAsset() );
		BuildingPart->UpdateToAsset();
		BuildingPart->RegisterAllComponents();
	}
}

UBuildingPartPrimaryDataAsset* UBuildSystem::GetCurrentHoldingBuildingPartPrimaryDataAsset() const
{
	return HoldingBuildingPartPrimaryDataAssets[CurrentHoldingBuildingPartPrimaryDataAssetIndex];
}

void UBuildSystem::AttemptUpdateBuildPreview()
{
		if( !BuildPreview.IsValid() ) return;
		BuildPreview->SetStaticMesh( GetCurrentHoldingBuildingPartPrimaryDataAsset()->GetItemStaticMesh() );
		BuildPreview->SetMaterial(0,Cast<UGlobalGameInstance>(UGameplayStatics::GetGameInstance(GetWorld()))->GetBuildPreviewPlaceableMaterial());
		// BuildPreview->RegisterComponent();
}


// Called when the game starts
void UBuildSystem::BeginPlay()
{
	Super::BeginPlay();

	UE_LOG( LogTemp, Warning, TEXT("UBuildingSystem::BeginPlay"));
}

// Called every frame
void UBuildSystem::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	if( BuildMode )
	{
		UpdateHitResults();
		
		if( USocketComponent* SnappedSocketComponent = GetSnappableSocketComponent() )
		{
			AttemptCreateBuildPreview();
			
			BuildPreview->SetWorldLocation( SnappedSocketComponent->GetBaseLocation() );
			BuildPreview->SetWorldRotation( SnappedSocketComponent->GetBaseRotation() );
		}
		else if( bBuildLocationHit )
		{
			AttemptCreateBuildPreview();
			BuildPreview->SetWorldLocation( HitResults.Last().Location );
		}
		else
		{
			AttemptDestroyBuildPreview();
		}
	}
}

void UBuildSystem::SwitchHoldingBuildingPartPrimaryDataAsset(const FInputActionValue& Value)
{
	float MouseWheelValue = Value.Get<float>();
	if( MouseWheelValue > 0.8 ) {
		CurrentHoldingBuildingPartPrimaryDataAssetIndex++;
	}
	else if( MouseWheelValue < 0.8 )
	{
		CurrentHoldingBuildingPartPrimaryDataAssetIndex--;
	}
	CurrentHoldingBuildingPartPrimaryDataAssetIndex =
		( CurrentHoldingBuildingPartPrimaryDataAssetIndex + HoldingBuildingPartPrimaryDataAssets.Num() )
			% HoldingBuildingPartPrimaryDataAssets.Num();

	AttemptUpdateBuildPreview();
}
