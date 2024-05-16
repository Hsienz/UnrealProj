// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemStaticMeshComponent.h"

#include "EnhancedInputComponent.h"
#include "..\..\Character\PlayerCharacter.h"
#include "RPG/ActorComponents/Equipment/EquipmentSystem.h"

APlayerCharacter* UItemStaticMeshComponent::GetCharacter()
{
	return AttachingCharacter.IsValid() ? AttachingCharacter.Get() : nullptr;
}

void UItemStaticMeshComponent::AttachToCharacter(APlayerCharacter* Character)
{
	AttachingCharacter = Character;

	if( !AttachingCharacter.IsValid() ) return;
	
	FAttachmentTransformRules AttachmentTransformRules( EAttachmentRule::SnapToTarget, true);
	// AttachToComponent( AttachingCharacter->GetMesh1P(),  AttachmentTransformRules, "GripPoint");
	UpdateEquipmentInputActions();
}

void UItemStaticMeshComponent::UpdateEquipmentInputActions()
{
	if( UEquipmentSystem* EquipmentSystem = AttachingCharacter->GetEquipmentSystem() )
	{
		if( UEnhancedInputComponent* EnhancedInputComponent = EquipmentSystem->GetEnhancedInputComponentRef() )
		{
			EnhancedInputComponent->BindAction(
				EquipmentSystem->GetInputAction(EEquipmentInputActionType::Left),
				LeftTriggerEvent,
				this,
				&UItemStaticMeshComponent::LeftUse);

			EnhancedInputComponent->BindAction(
				EquipmentSystem->GetInputAction(EEquipmentInputActionType::Right),
				RightTriggerEvent,
				this,
				&UItemStaticMeshComponent::RightUse);			
		}
	}
}

void UItemStaticMeshComponent::LeftUse_Implementation()
{
	IItemMeshComponent::LeftUse_Implementation();
}

void UItemStaticMeshComponent::RightUse_Implementation()
{
	IItemMeshComponent::RightUse_Implementation();
}
