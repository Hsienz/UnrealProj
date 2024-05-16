// Fill out your copyright notice in the Description page of Project Settings.


#include "Shield.h"

#include "AbilitySystemComponent.h"
#include "AbilitySystemInterface.h"
#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "RPG/ActorComponents/Montage/MontageComponent.h"
#include "RPG/Interfaces/HasMontageComponent.h"


// Sets default values
AShield::AShield()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AShield::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AShield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AShield::RightUse_Implementation()
{
	Super::RightUse_Implementation();
	HoldShield();
}

void AShield::HoldShield()
{
	bIsHoldingShield = true;
	if( CharacterRef.IsValid() )
	{
		CharacterRef->GetCharacterMovement()->MaxWalkSpeed = 200;
		if( IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(CharacterRef) )
		{
			FGameplayTagContainer Container;
			Container.AddTag( FGameplayTag::RequestGameplayTag("Character.Action.HoldingShield"));
			AbilitySystemInterface->GetAbilitySystemComponent()->TryActivateAbilitiesByTag( Container );
		}
	}
}

void AShield::ReleaseShield()
{
	bIsHoldingShield = false;
	if( CharacterRef.IsValid() )
	{
		CharacterRef->GetCharacterMovement()->MaxWalkSpeed = 500;
		if( IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>( CharacterRef ))
		{
			FGameplayTagContainer Container;
			Container.AddTag( FGameplayTag::RequestGameplayTag("Character.Action.HoldingShield"));
			AbilitySystemInterface->GetAbilitySystemComponent()->CancelAbilities( &Container );
		}
	}
}

void AShield::RightRelease()
{
	ReleaseShield();
}

UAnimMontage* AShield::GetHoldingShieldMontage() const
{
	return HoldingShieldMontage;
}
