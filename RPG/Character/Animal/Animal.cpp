// Fill out your copyright notice in the Description page of Project Settings.


#include "Animal.h"

#include "AIController.h"
#include "NavigationSystem.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Kismet/KismetSystemLibrary.h"
#include "RPG/ActorComponents/LimitedValue/Health.h"
#include "RPG/ActorComponents/Montage/MontageComponent.h"
#include "..\PlayerCharacter.h"
#include "Runtime/AIModule/Classes/Perception/PawnSensingComponent.h"


// Sets default values
AAnimal::AAnimal()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//bUseControllerRotationYaw = false;
	//GetCharacterMovement()->bUseControllerDesiredRotation = true;
	
	PawnSensingComponent = CreateDefaultSubobject<UPawnSensingComponent>(TEXT("PawnSensing"));
	MontageComponent = CreateDefaultSubobject<UMontageComponent>(TEXT("MontageComponent"));
	Health = CreateDefaultSubobject<UHealth>(TEXT("Health"));


	if( GetLocalRole() == ROLE_Authority )
		PawnSensingComponent->OnSeePawn.AddDynamic(this,&AAnimal::OnSeePawn);
	
}

UHealth* AAnimal::GetHealth_Implementation()
{
	return Health;
}

// Called when the game starts or when spawned
void AAnimal::BeginPlay()
{
	Super::BeginPlay();
	if( GetLocalRole() == ROLE_Authority )
	{
		RoamAround();
	}
}

void AAnimal::HandleDead_Implementation()
{
	IDamageable::HandleDead_Implementation();
}


void AAnimal::PreInitializeComponents()
{
	Super::PreInitializeComponents();
	OriginalMaxWalkSpeed = GetCharacterMovement()->MaxWalkSpeed;
	
}

// Called every frame
void AAnimal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void AAnimal::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void AAnimal::HandleAttackNotify(FName NotifyName, const FBranchingPointNotifyPayload& Payload)
{
	TArray<FHitResult> HitResults;
	FVector Start = GetActorLocation();
	FVector End = Start + GetActorForwardVector() * 100;
	TArray<TEnumAsByte<EObjectTypeQuery>> ObjectTypes;
	ObjectTypes.Add( UEngineTypes::ConvertToObjectType( ECC_Pawn ));
	UKismetSystemLibrary::SphereTraceMultiForObjects(
		GetWorld(),
		Start,
		End,
		20,
		ObjectTypes,
		false,
		{},
		EDrawDebugTrace::ForDuration,
		HitResults,
		true
		);
	for( FHitResult& HitResult: HitResults)
	{
		if( APlayerCharacter* Character = Cast<APlayerCharacter>(HitResult.GetActor()))
		{
			UGameplayStatics::ApplyDamage( Character, 10, GetInstigatorController(), this, nullptr); 
		}
	}
	GetMesh()->GetAnimInstance()->OnPlayMontageNotifyBegin.RemoveDynamic(this, &AAnimal::HandleAttackNotify);
}

void AAnimal::HandleAttackMontageEnd(UAnimMontage* Montage, bool bInterrupt)
{
	UActionLibrary::CountdownCooldown( GetWorld(), AttackAction );
}

void AAnimal::OnMoveComplete_SeePawn_Implementation(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	switch( Result)
	{
	case EPathFollowingResult::Success:
		if( AttackAction.Montage )
		{
			UAnimInstance* AnimInstance = GetMesh()->GetAnimInstance();
			if( AnimInstance )
			{
				UActionLibrary::StartCooldown( AttackAction );
				MontageComponent->ServerMulticastMontagePlay( AttackAction.Montage);
				FOnMontageEnded OnMontageEnded = FOnMontageEnded::CreateUObject( this, &AAnimal::HandleAttackMontageEnd );
				
				AnimInstance->OnPlayMontageNotifyBegin.AddDynamic(this,&AAnimal::HandleAttackNotify);
				AnimInstance->Montage_SetEndDelegate( OnMontageEnded , AttackAction.Montage );
			}
		}
		break;
		default:
			break;
	}
	if( AAIController* AIController = Cast<AAIController>(GetController())) {
		AIController->ReceiveMoveCompleted.RemoveDynamic( this, &AAnimal::OnMoveComplete_SeePawn );
	}
}

void AAnimal::OnSeePawn_Implementation(APawn* TargetPawn)
{
	if( Cast<APlayerCharacter>( TargetPawn) )
	{
		if( AAIController* AIController = GetController<AAIController>() )
		{
			GetCharacterMovement()->MaxWalkSpeed = MaxSprintSpeed;
			AIController->MoveToLocation(
				TargetPawn->GetActorLocation(),
				StopDistance
			);
			if( !AttackAction.bIsCooldown )
			{
				AIController->ReceiveMoveCompleted.AddUniqueDynamic(this,&AAnimal::AAnimal::OnMoveComplete_SeePawn);
			}
		}
		
	}
}

void AAnimal::OnMoveComplete_Roam_Implementation(FAIRequestID RequestID, EPathFollowingResult::Type Result)
{
	switch ( Result )
	{
	case EPathFollowingResult::Success:
		GetWorldTimerManager().SetTimer( TimerHandle, this, &AAnimal::RoamAround, 2, false);
		break;
		default:
			break;
		
	}
	if( AAIController* AIController = Cast<AAIController>(GetController())) {
		AIController->ReceiveMoveCompleted.RemoveDynamic( this, &AAnimal::OnMoveComplete_Roam );
	}
}

void AAnimal::RoamAround_Implementation()
{

	if( !GetWorld() ) return ;
	if( UNavigationSystemV1* NavigationSystemV1 = UNavigationSystemV1::GetCurrent(GetWorld()) )
	{
		FNavLocation RandomPoint;
		bool CanNav = NavigationSystemV1->GetRandomPointInNavigableRadius(
			GetActorLocation(),
			RoamDistance,
			RandomPoint
		);

		if( !CanNav ) return;

		AAIController* AIController = GetController<AAIController>();
		
		if( !AIController ) return;
		
		EPathFollowingRequestResult::Type Result = AIController->MoveToLocation(
		RandomPoint,
		StopDistance
		);
		AIController->ReceiveMoveCompleted.AddDynamic(this, &AAnimal::OnMoveComplete_Roam);
	}
}

