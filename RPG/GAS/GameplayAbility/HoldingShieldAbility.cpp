// Fill out your copyright notice in the Description page of Project Settings.


#include "HoldingShieldAbility.h"

#include "Abilities/Tasks/AbilityTask_PlayMontageAndWait.h"
#include "RPG/Actor/Shield.h"
#include "RPG/Component/Equipment/EquipmentActorComponent.h"
#include "RPG/Component/Equipment/EquipmentManager.h"
#include "RPG/Interfaces/HasEquipmentManager.h"

UHoldingShieldAbility::UHoldingShieldAbility()
{
	AbilityTags.AddTag( FGameplayTag::RequestGameplayTag(FName("Character.Action.HoldingShield")));
	ActivationOwnedTags.AddTag( FGameplayTag::RequestGameplayTag(FName("Character.Status.IsHoldingShield")));
	CancelAbilitiesWithTag.AddTag(FGameplayTag::RequestGameplayTag(FName("Character.Action.Sprint")));
}

void UHoldingShieldAbility::ActivateAbility(const FGameplayAbilitySpecHandle Handle,
                                            const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
                                            const FGameplayEventData* TriggerEventData)
{
	Super::ActivateAbility(Handle, ActorInfo, ActivationInfo, TriggerEventData);
	AShield* EquippedShield = Cast<AShield>(
		IHasEquipmentManager::Execute_GetEquipmentManager(ActorInfo->AvatarActor.Get() )
			->GetEquipmentByType( EEquipmentType::LeftHand )
			->GetChildActor() );
	if( !EquippedShield ) return;
	CommitAbility(Handle, ActorInfo, ActivationInfo );
	auto Task = UAbilityTask_PlayMontageAndWait::CreatePlayMontageAndWaitProxy( this, NAME_None,
			EquippedShield->GetHoldingShieldMontage() );
	Task->ReadyForActivation();

	// end ability when right mouse button release
	// EndAbility(Handle, ActorInfo, ActivationInfo, false, false );
	
}

void UHoldingShieldAbility::EndAbility(const FGameplayAbilitySpecHandle Handle,
	const FGameplayAbilityActorInfo* ActorInfo, const FGameplayAbilityActivationInfo ActivationInfo,
	bool bReplicateEndAbility, bool bWasCancelled)
{
	Super::EndAbility(Handle, ActorInfo, ActivationInfo, bReplicateEndAbility, bWasCancelled);
}
