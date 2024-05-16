// Fill out your copyright notice in the Description page of Project Settings.


#include "DodgeAbility.h"

#include "MotionWarpingComponent.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RPG/Character/PlayerCharacter.h"
#include "RPG/Interfaces/HasMotionWrappingComponent.h"

UDodgeAbility::UDodgeAbility()
{
	AbilityTags.AddTag( FGameplayTag::RequestGameplayTag(FName("Character.Action.Vault")));
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Status.IsDodging")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Status.IsDodging")));
}

bool UDodgeAbility::TraceMain_Implementation(FHitResult& HitResult)
{
	// if character is player dodge to input direction, else dodge to random direction like enemy
	if( APlayerCharacter* Player = Cast<APlayerCharacter>( GetActorInfo().AvatarActor ) )
	{
		FVector Direction = Player->GetCharacterMovement()->GetLastInputVector();
		if( Direction.IsZero() ) Direction = Player->GetActorForwardVector();
		return TraceHV( Direction , HitResult);
	}
	else
	{
		FVector RandomDirection = FMath::VRand();
		RandomDirection.Z = 0;
		RandomDirection.Normalize();
		return TraceHV( RandomDirection, HitResult );
	}
}

bool UDodgeAbility::TraceHV(const FVector& Direction, FHitResult& HitResult)
{
	FVector StartLocation = GetActorInfo().AvatarActor->GetActorLocation();
	FVector PrevLocation = StartLocation;
	bool bIsHit = false;
	for( int i = 1 ; i <= TraceInfo.TraceCount; i++ )
	{
		FVector EndLocation = StartLocation + Direction * i * TraceInfo.TraceGap;
		// check if there are obstacle blocked on the way
		if( !Trace( GetWorld(), PrevLocation, EndLocation, HitResult)
			&& !HitResult.bBlockingHit )
		{
			bIsHit = true;
			// check if there are ground to stand
			if( TraceV( EndLocation, HitResult) )
			{
				PrevLocation = EndLocation;
			}
			// if we can dodge thru the gap, we need to keep trace, or just stop the trace
			else if( !CanCrossThruGap ) break;
		}
		else break;
	}
	return bIsHit;
}

bool UDodgeAbility::TraceV(const FVector& StartLocation, FHitResult& HitResult)
{
	FVector OffsetStartLocation = StartLocation;
	OffsetStartLocation.Z += TraceInfo.VerticalOffset;
	FVector EndLocation = OffsetStartLocation;
	EndLocation.Z -= TraceInfo.MaxVerticalDistance;
	return Trace( GetWorld(), OffsetStartLocation, EndLocation, HitResult);
}

void UDodgeAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CommitAbility(Handle, ActorInfo, ActivationInfo );
	FHitResult HitResult;
	bool bIsHit = TraceMain(HitResult );
	if( bIsHit )
	{
		ActorInfo->AvatarActor->SetActorEnableCollision( false);
		Cast<ACharacter>( ActorInfo->AvatarActor )->GetCharacterMovement()->SetMovementMode( MOVE_Flying );
		SetupDodgeMotionWarping( HitResult.Location );
		auto Task = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(this, NAME_None, DodgeMontage );
		Task->OnCompleted.AddDynamic( this, &UDodgeAbility::K2_EndAbility );
		Task->ReadyForActivation();
	}
	else K2_EndAbility();
}

void UDodgeAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	ActorInfo->AvatarActor->SetActorEnableCollision( true);
	Cast<ACharacter>( ActorInfo->AvatarActor )->GetCharacterMovement()->SetMovementMode( MOVE_Walking );
	
}

void UDodgeAbility::SetupDodgeMotionWarping(const FVector& LandLocation)
{
	IHasMotionWrappingComponent::Execute_GetMotionWarpingComponent( GetActorInfo().AvatarActor.Get() )->AddOrUpdateWarpTargetFromLocation(
		"LandLocation",
		LandLocation
	);
}
