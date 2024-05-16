// Fill out your copyright notice in the Description page of Project Settings.


#include "VaultAbility.h"

#include "MotionWarpingComponent.h"
#include "Kismet/KismetSystemLibrary.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RPG/Character/PlayerCharacter.h"

UVaultAbility::UVaultAbility()
{
	AbilityTags.AddTag( FGameplayTag::RequestGameplayTag(FName("Character.Action.Vault")) );
	ActivationOwnedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Status.IsVaulting")));
	ActivationBlockedTags.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Status.IsVaulting")));
}

void UVaultAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
                                    const FGameplayAbilityActivationInfo ActivationInfo, const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	CommitAbility(Handle, ActorInfo, ActivationInfo);
	FHitResult HitResult;
	TraceMain( HitResult );
	if( LandToLocationExist && VaultMontage )
	{
		ActorInfo->AvatarActor->SetActorEnableCollision(false);
		Cast<ACharacter>(ActorInfo->AvatarActor)->GetCharacterMovement()->SetMovementMode(MOVE_Flying);
		SetupMotionWarping();
		UAbilityTask_PlayMontageAndWait* MontageTask = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy(
			this,
			NAME_None,
			VaultMontage
		);
		MontageTask->OnCompleted.AddDynamic(this, &UVaultAbility::K2_EndAbility );
		MontageTask->ReadyForActivation();
	}
	else K2_EndAbility();
}

void UVaultAbility::EndAbility(const FGameplayAbilitySpecHandle Handle, const FGameplayAbilityActorInfo* ActorInfo,
	const FGameplayAbilityActivationInfo ActivationInfo, bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
	ActorInfo->AvatarActor->SetActorEnableCollision(true);
	Cast<ACharacter>(ActorInfo->AvatarActor)->GetCharacterMovement()->SetMovementMode(MOVE_Walking);
}

void UVaultAbility::SetupMotionWarping()
{
	if( APlayerCharacter* Player = Cast<APlayerCharacter>(GetActorInfo().AvatarActor) )
	{
		UMotionWarpingComponent* MotionWrappingComponent = IHasMotionWrappingComponent::Execute_GetMotionWarpingComponent( Player );
		MotionWrappingComponent->AddOrUpdateWarpTargetFromLocation(
			"JumpToLocation",
			JumpToLocation
		);
		MotionWrappingComponent->AddOrUpdateWarpTargetFromLocation(
			"MidLocation",
			MidLocation
		);
		MotionWrappingComponent->AddOrUpdateWarpTargetFromLocation(
			"LandToLocation",
			LandToLocation
		);
	}
}

bool UVaultAbility::TraceMain_Implementation(FHitResult& HitResult)
{
	for( int32 i = 1; i <= LoopCount; i++ )
	{
		FVector Start = GetActorInfo().AvatarActor->GetActorLocation() + GetActorInfo().AvatarActor->GetActorForwardVector() * i * TraceGap;
		Start.Z += TraceStartOffset;
		FVector End = Start;
		End.Z -= TraceLength;
		bool IsHit = Trace( GetWorld(), Start, End, HitResult );

		// if hit a obstacle too tall, then the character must must not vault
		if( IsHit && HitResult.bStartPenetrating ) {
			break;
		}

		// init the location we jump up to
		if( !JumpToLocationExist && IsHit )
		{
			JumpToLocationExist = true;
			JumpToLocation = HitResult.Location;
		}

		// test if we can land on opposite ground, too high or too low are not allow
		if( !IsHit && JumpToLocationExist )
		{
			MidLocation = HitResult.TraceEnd;
			Start = GetActorInfo().AvatarActor->GetActorLocation() + GetActorInfo().AvatarActor->GetActorForwardVector() * ( i * TraceGap + LandHorizonDistance);
			Start.Z += TraceStartOffset;
			End = Start;
			End.Z -= LandVerticalDistance;
			IsHit = Trace( GetWorld(), Start,End,HitResult);
			if( IsHit )
			{
				LandToLocationExist = true;
				LandToLocation = HitResult.Location;
			}
			break;
		}
	}
	return JumpToLocationExist && LandToLocationExist;
}
