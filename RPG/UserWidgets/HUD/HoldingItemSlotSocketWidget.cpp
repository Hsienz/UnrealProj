// Fill out your copyright notice in the Description page of Project Settings.


#include "HoldingItemSlotSocketWidget.h"

#include "..\..\Character\PlayerCharacter.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "RPG/Component/Item/ItemSkeletalMeshComponent.h"
#include "RPG/Component/Item/ItemStaticMeshComponent.h"
#include "RPG/Interfaces/ItemMeshComponent.h"
#include "RPG/PrimaryDataAssets/ItemPrimaryDataAsset.h"
#include "RPG/UserWidgets/ItemSlotWidget.h"
#include "Components/Border.h"
#include "Components/ScaleBox.h"
#include "RPG/Struct/ItemSlot.h"

void UHoldingItemSlotSocketWidget::HandleOnSelect()
{
	Border->SetBrushColor( FLinearColor( SelectColor ) );
}

void UHoldingItemSlotSocketWidget::HandleOnUnselect()
{
	Border->SetBrushColor( OriginColor );
}

void UHoldingItemSlotSocketWidget::AttachToComponent()
{
	if( SlotWidgetToUpdate->GetChildrenCount() )
	{
		if( UItemSlotWidget* ItemSlotWidget = Cast<UItemSlotWidget>(SlotWidgetToUpdate->GetChildAt(0)))
		{
			IItemMeshComponent* ItemMeshComponent = nullptr;
			if( USkeletalMesh* SkeletalMesh = ItemSlotWidget->GetInventorySlot()->ItemAsset->GetItemSkeletalMesh() )
			{
				UItemSkeletalMeshComponent* MeshComponent = NewObject<UItemSkeletalMeshComponent>();
				MeshComponent->SetSkeletalMesh( SkeletalMesh );
				ItemMeshComponent = Cast<IItemMeshComponent>(MeshComponent);
			}
			else if( UStaticMesh* StaticMesh = ItemSlotWidget->GetInventorySlot()->ItemAsset->GetItemStaticMesh() )
			{
				UItemStaticMeshComponent* MeshComponent = NewObject<UItemStaticMeshComponent>();
				MeshComponent->SetStaticMesh(StaticMesh);
				ItemMeshComponent = Cast<IItemMeshComponent>(MeshComponent);
			}

			if( ItemMeshComponent )
			{
				ItemMeshComponent->AttachToCharacter( Cast<APlayerCharacter>(GetOwningPlayerPawn()));
			}
		}
	}
}

void UHoldingItemSlotSocketWidget::NativeConstruct()
{
	Super::NativeConstruct();
	OriginColor = Border->GetBrushColor();
	
}
