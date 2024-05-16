// Fill out your copyright notice in the Description page of Project Settings.


#include "Bow.h"

#include "Components/ArrowComponent.h"
#include "Components/PoseableMeshComponent.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/KismetMathLibrary.h"
#include "Net/UnrealNetwork.h"
#include "Projectile/Arrow.h"
#include "..\Character\PlayerCharacter.h"
#include "Kismet/GameplayStatics.h"
#include "RPG/ActorComponents/Montage/MontageComponent.h"
#include "RPG/Component/Equipment/EquipmentActorComponent.h"
#include "RPG/Component/Equipment/EquipmentManager.h"


// Sets default values
ABow::ABow()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	RightTriggerEvent = ETriggerEvent::Ongoing;
	ArrowOutLocation = CreateDefaultSubobject<UArrowComponent>(TEXT("ArrowOutLocation"));
	ArrowOutLocation->SetupAttachment( PoseableMesh );
}

// Called when the game starts or when spawned
void ABow::BeginPlay()
{
	Super::BeginPlay();
	
}

void ABow::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME( ABow, bIsAiming );
}

// Called every frame
void ABow::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if( bIsAiming )
	{
		AttachStringToOtherHand();
		// ArrowRelocation();
	}
}

void ABow::LeftUse_Implementation()
{
	// Super::LeftUse_Implementation();
	UE_LOG(LogTemp,Log,TEXT("Bow"));
	if( bIsAiming )
	{
		ShootArrow();
	}
}

void ABow::RightUse_Implementation()
{
	// Super::RightUse_Implementation();
	UE_LOG( LogTemp, Log, TEXT("Aiming"));
	if( bIsAiming )
	{
		StopAiming();
		if( ArrowActor.IsValid() )
		{
			ArrowActor->Destroy();
		}
	}
	else DrawArrow();
}

void ABow::OnPlayMontageNotifyBegin_AttachString(FName Name, const FBranchingPointNotifyPayload& Payload)
{
	if( Name == "HoldArrow" )
	{
		if( BP_Projectile && CharacterRef.IsValid() )
		{
			SpawnArrow();
		}
	}
	else if ( Name == "AttachStringToHand" )
	{
		StartAiming();
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Unknown Notify Name:%s"), *Name.ToString() );
	}
	// GetAnimInstance()->OnPlayMontageNotifyBegin.RemoveDynamic(this, &ABow::ABow::OnPlayMontageNotifyBegin_AttachString );
}

void ABow::OnMontageEnded_StartAiming(UAnimMontage* Montage, bool bInterrupted)
{
	StartAiming();
}

void ABow::AfterShoot(UAnimMontage* Montage, bool bInterrupted)
{
	UE_LOG( LogTemp, Warning, TEXT("AfterShoot"));
	ResetString();
	DrawArrow();
	GetAnimInstance()->Montage_GetEndedDelegate()->Unbind();
}

void ABow::SpawnArrow()
{
	ArrowActor = GetWorld()->SpawnActor<AArrow>( BP_Projectile, GetActorLocation(), GetActorRotation() );
	ArrowActor->SetCharacterRef( CharacterRef.IsValid() ? CharacterRef.Get() : nullptr );
	FAttachmentTransformRules Rules( EAttachmentRule::SnapToTarget, true );
	ArrowActor->AttachToComponent( Cast<IHasEquipmentManager>(CharacterRef.Get())->GetEquipmentManager()->GetEquipmentByType(EEquipmentType::RightHand), Rules );
	UE_LOG(LogTemp,Log,TEXT( "%p,%s" ), CharacterRef.Get(), *CharacterRef->GetActorLocation().ToString() );
}


void ABow::AttachStringToOtherHand() 
{
	if( !CharacterRef.IsValid() ) return;
	PoseableMesh->SetBoneLocationByName( StringName,
		Cast<IHasEquipmentManager>(CharacterRef.Get())->
		GetEquipmentManager()->
		GetEquipmentByType( EEquipmentType::RightHand )->GetComponentLocation(), EBoneSpaces::WorldSpace);
}

void ABow::ArrowRelocation()
{
	if( CharacterRef.IsValid() && BodySocketRef.IsValid() )
	{
		FVector HandLocation = BodySocketRef->GetComponentLocation();
		if( ArrowActor.IsValid() )
		{
			UE_LOG( LogTemp, Log, TEXT("Hand:%s Arrow:%s"), *HandLocation.ToString(), *ArrowOutLocation->GetComponentLocation().ToString() );
			ArrowActor->SetActorRotation( UKismetMathLibrary::FindLookAtRotation(
				HandLocation,
				ArrowOutLocation->GetComponentLocation()
			));
		}
	}
}

void ABow::StartAiming()
{
	bIsAiming = true;
	if( CharacterRef.IsValid())
	{
		CharacterRef->GetCharacterMovement()->bUseControllerDesiredRotation = true;
		CharacterRef->GetCharacterMovement()->bOrientRotationToMovement = false;
	}
}

void ABow::StopAiming()
{
	bIsAiming = false;
	ResetString();
	CharacterRef->GetCharacterMovement()->bUseControllerDesiredRotation = false;
	CharacterRef->GetCharacterMovement()->bOrientRotationToMovement = true;
}

bool ABow::IsAiming() const
{
	return bIsAiming;
}

void ABow::DrawArrow()
{
	if( !CharacterRef.IsValid()) return;
	Cast<IHasMontageComponent>( CharacterRef )->GetMontageSystem()->ServerMulticastMontagePlay( DrawArrowMontage );
	GetAnimInstance()->OnPlayMontageNotifyBegin.AddUniqueDynamic( this, &ABow::OnPlayMontageNotifyBegin_AttachString );
}

void ABow::ShootArrow()
{
	if( !CharacterRef.IsValid() ) return;
	Cast<IHasMontageComponent>( CharacterRef.Get() )->GetMontageSystem()->ServerMulticastMontagePlay(ShootArrowMontage);
	StopAiming();
	if( ArrowActor.IsValid() )
	{
		FDetachmentTransformRules Rules(EDetachmentRule::KeepWorld, false );
		ArrowActor->DetachFromActor(Rules);
		ArrowActor->Launch();
		ArrowActor = nullptr;
	}
	GetAnimInstance()->Montage_GetEndedDelegate(ShootArrowMontage)->BindUObject( this, &ABow::AfterShoot );
}

void ABow::ResetString()
{
	PoseableMesh->ResetBoneTransformByName( StringName );
}
