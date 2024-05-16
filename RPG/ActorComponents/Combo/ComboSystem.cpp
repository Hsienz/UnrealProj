// Fill out your copyright notice in the Description page of Project Settings.


#include "ComboSystem.h"

#include "GameFramework/Character.h"
#include "RPG/ActorComponents/Montage/MontageComponent.h"
#include "RPG/Interfaces/HasMontageComponent.h"


// Sets default values for this component's properties
UComboSystem::UComboSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	// ...
}

void UComboSystem::ProcessCombo(FComboSequence& ComboSequence, bool bLock)
{
	// if combo is locked, we can not process any combo, it is kind same as cooldown of attack animation
	if( bIsLock ) return;
	ProcessCheckSameComboSequenceAndSet( ComboSequence );
	if( UMontageComponent* MontageComponent = IHasMontageComponent::Execute_GetMontageSystem(GetOwner()))
	{
		auto CurrentComboPtr = ComboSequence[ComboIndex];
		if( !CurrentComboPtr.IsValid() )
		{
			UE_LOG( LogTemp, Error, TEXT("ProcessCombo: CurrentComboPtr is not valid, ComboIndex: %d"), ComboIndex);
			ResetCombo();
		}
		else
		{
			MontageComponent->ServerMulticastMontagePlay( CurrentComboPtr->AttackMontage);
			NextCombo();
			if( bLock ) LockCombo();
		}
	}
}

void UComboSystem::LockCombo()
{
	bIsLock = true;
}

void UComboSystem::UnlockCombo()
{
	bIsLock = false;
}

void UComboSystem::ResetCombo()
{
	UE_LOG( LogTemp, Log, TEXT("Reset"));
	ComboIndex = 0;
	UnlockCombo();
	ClearHitActor();
}

void UComboSystem::ClearHitActor()
{
	HitActor.Empty();
}

void UComboSystem::AddHitActor(AActor* Actor)
{
	if( !HitActor.Contains(Actor) ) HitActor.Add( Actor );
}

bool UComboSystem::IsActorHit(AActor* Actor)
{
	return HitActor.Contains(Actor);
}

void UComboSystem::NextCombo()
{
	if( !LatestComboSharedPtr.IsValid() )
	{
		ResetCombo();
	}
	else
	{
		ComboIndex = ++ComboIndex % LatestComboSharedPtr->Combos.Num();
		ClearHitActor();
	}
	UE_LOG( LogTemp, Log, TEXT("ComboIndex: %d"), ComboIndex);
}



void UComboSystem::ProcessCheckSameComboSequenceAndSet(FComboSequence& ComboSequence)
{
	/*
	UE_LOG( LogTemp,Log,TEXT("LatestComboPtr: %p \n Current: %p \n Origin: %p \n 1: %d \n 2: %d \n 3: %d"),
		&LatestComboSharedPtr.ToSharedRef(),
		&ComboSequenceSharedPtr.ToSharedRef(),
		&ComboSequence,
		LatestComboSharedPtr == ComboSequenceSharedPtr,
		LatestComboSharedPtr.ToWeakPtr().HasSameObject( &ComboSequence ),
		3 );
	*/
	// if it's not same combo sequence reset combo
	if( !LatestComboSharedPtr.IsValid() || LatestComboPtr != &ComboSequence )
	{
		ResetCombo();
		LatestComboSharedPtr = MakeShared<FComboSequence>( ComboSequence );
		LatestComboPtr = &ComboSequence;
	}
	
}

