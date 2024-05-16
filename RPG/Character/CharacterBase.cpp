// Fill out your copyright notice in the Description page of Project Settings.


#include "CharacterBase.h"

#include "AbilitySystemComponent.h"
#include "RPG/GAS/AbilitySystemComponent/EnhancedAbilitySystemComponent.h"
#include "RPG/GAS/GameplayAbility/EnhancedGameplayAbility.h"


// Sets default values
ACharacterBase::ACharacterBase()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void ACharacterBase::BeginPlay()
{
	Super::BeginPlay();
	
}

UAbilitySystemComponent* ACharacterBase::GetAbilitySystemComponent() const
{
	return AbilitySystemComponentPtr.Get();
}

// Called every frame
void ACharacterBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void ACharacterBase::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);
}

void ACharacterBase::GiveDefaultAbilities()
{
	if( AbilitySystemComponentPtr.IsValid() && GetLocalRole() == ROLE_Authority )
	{
		for( TSubclassOf<UEnhancedGameplayAbility>& Ability : Abilities )
		{
			if( Ability )
			{
				AbilitySystemComponentPtr->GiveAbility( FGameplayAbilitySpec(
					Ability,
					1,
					static_cast<int32>( Ability.GetDefaultObject()->GetAbilityBindingId() ) ,
					this ) );
			}
		}
	}
}

void ACharacterBase::ApplyDefaultEffects()
{
	if( AbilitySystemComponentPtr.IsValid() && GetLocalRole() == ROLE_Authority )
	{
		for( TSubclassOf<UGameplayEffect>& Effect: Effects)
		{
			if( Effect )
			{
				FGameplayEffectContextHandle EffectContextHandle = AbilitySystemComponentPtr->MakeEffectContext();
				EffectContextHandle.AddSourceObject(this);

				FGameplayEffectSpecHandle EffectSpecHandle = AbilitySystemComponentPtr->MakeOutgoingSpec(Effect, 1, EffectContextHandle);
 
				if( EffectSpecHandle.IsValid() )
				{
					AbilitySystemComponentPtr->ApplyGameplayEffectSpecToSelf( *EffectSpecHandle.Data.Get() );
				}
			}
		}
	}
}

