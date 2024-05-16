// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemSkeletalMeshComponent.h"

#include "EnhancedInputComponent.h"
#include "..\..\Character\PlayerCharacter.h"
#include "RPG/ActorComponents/Equipment/EquipmentSystem.h"

APlayerCharacter* UItemSkeletalMeshComponent::GetCharacter()
{
	return AttachingCharacter.IsValid() ? AttachingCharacter.Get() : nullptr;
}

void UItemSkeletalMeshComponent::AttachToCharacter(APlayerCharacter* Character)
{
	AttachingCharacter = Character;

	if( !AttachingCharacter.IsValid() ) return;
	
	FAttachmentTransformRules AttachmentTransformRules( EAttachmentRule::SnapToTarget, true);
	// AttachToComponent( AttachingCharacter->GetMesh1P(),  AttachmentTransformRules, "GripPoint");
	UpdateEquipmentInputActions();
}

void UItemSkeletalMeshComponent::UpdateEquipmentInputActions()
{
	if( UEquipmentSystem* EquipmentSystem = AttachingCharacter->GetEquipmentSystem() )
	{
		if( UEnhancedInputComponent* EnhancedInputComponent = EquipmentSystem->GetEnhancedInputComponentRef() )
		{
			EnhancedInputComponent->BindAction(
				EquipmentSystem->GetInputAction(EEquipmentInputActionType::Left),
				LeftTriggerEvent,
				this,
				&UItemSkeletalMeshComponent::LeftUse);

			EnhancedInputComponent->BindAction(
				EquipmentSystem->GetInputAction(EEquipmentInputActionType::Right),
				RightTriggerEvent,
				this,
				&UItemSkeletalMeshComponent::RightUse);			
		}
	}
}

void UItemSkeletalMeshComponent::LeftUse_Implementation()
{
	IItemMeshComponent::LeftUse_Implementation();
}

void UItemSkeletalMeshComponent::RightUse_Implementation()
{
	IItemMeshComponent::RightUse_Implementation();
}
