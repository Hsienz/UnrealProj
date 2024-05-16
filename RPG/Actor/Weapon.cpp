// Fill out your copyright notice in the Description page of Project Settings.


#include "Weapon.h"

#include "Kismet/GameplayStatics.h"
#include "RPG/ActorComponents/Combo/ComboSystem.h"
#include "RPG/Character/PlayerCharacter.h"
#include "AbilitySystemBlueprintLibrary.h"
#include "AbilitySystemComponent.h"
#include "Shield.h"
#include "RPG/Component/Equipment/EquipmentActorComponent.h"
#include "RPG/Component/Equipment/EquipmentManager.h"

// Sets default values
AWeapon::AWeapon()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
}

// Called when the game starts or when spawned
void AWeapon::BeginPlay()
{
	Super::BeginPlay();
	ComboSystem = IHasComboSystem::Execute_GetComboSystem( UGameplayStatics::GetPlayerCharacter(GetWorld(),0) );
}

// Called every frame
void AWeapon::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AWeapon::LeftUse_Implementation()
{
	Super::LeftUse_Implementation();
	/*
	if( !CharacterRef.IsValid() ) return;
	Combos.ProcessCombo(  CharacterRef->GetMontageComponent() );
	*/
	// Cast<IHasComboSystem>( UGameplayStatics::GetPlayerCharacter(GetWorld(),0) )->GetComboSystem()->ProcessCombo( Combos );
	if( ComboSystem.IsValid() ) ComboSystem->ProcessCombo(Combos );
}

void AWeapon::StartDamageTrace_Implementation()
{
	GetWorldTimerManager().SetTimer( DamageTraceHandle, FTimerDelegate::CreateUObject( this, &AWeapon::DamageTrace ), DamageTraceRate, true );
}

void AWeapon::StopDamageTrace_Implementation()
{
	GetWorldTimerManager().ClearTimer( DamageTraceHandle );
}

void AWeapon::TryApplyDamageToTarget(AActor* Actor)
{
	if( DetermineIfTraceOnShieldBeforeApplyDamage( Actor ) ) return;
	if( Cast<IDamageable>(Actor) && !ComboSystem->IsActorHit(Actor) )
	{
		UGameplayStatics::ApplyDamage( Actor, 10, CharacterRef.IsValid() ? CharacterRef->GetInstigatorController() : nullptr, this, nullptr);
		ComboSystem->AddHitActor( Actor );
	}
}

bool AWeapon::DetermineIfTraceOnShieldBeforeApplyDamage(AActor* Actor)
{
	IAbilitySystemInterface* AbilitySystemInterface = Cast<IAbilitySystemInterface>(Actor);
	if( !AbilitySystemInterface ) return false;
	if( UAbilitySystemComponent* AbilitySystemComponent = AbilitySystemInterface->GetAbilitySystemComponent() )
	{
		if( AbilitySystemComponent->HasMatchingGameplayTag( FGameplayTag::RequestGameplayTag("Character.Status.IsHoldingShield")))
		{
			UEquipmentManager* EquipmentManager = IHasEquipmentManager::Execute_GetEquipmentManager( Actor );
			AShield* Shield = Cast<AShield>( EquipmentManager->GetEquipmentByType( EEquipmentType::LeftHand )->GetChildActor() );
			TraceOnShield( Shield );
			return true;
		}
	}
	return false;
}


void AWeapon::TraceOnShield_Implementation( AShield* Shield )
{
	if( Shield && Shield->GetCharacterRef() ) ComboSystem->AddHitActor( Shield->GetCharacterRef() );
}

void AWeapon::DamageTrace_Implementation()
{
}

