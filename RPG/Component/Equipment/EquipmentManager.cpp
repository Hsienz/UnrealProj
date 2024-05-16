// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentManager.h"

#include "EquipmentActorComponent.h"
#include "Components/SceneCaptureComponent2D.h"
#include "RPG/ActorComponents/InventorySystem.h"
#include "RPG/Character/PlayerCharacter.h"
#include "RPG/Struct/ItemSlot.h"


// Sets default values for this component's properties
UEquipmentManager::UEquipmentManager()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;

	EquipmentInventory = CreateDefaultSubobject<UInventorySystem>(TEXT("EquipmentInventory"));
	// ...
}


// Called when the game starts
void UEquipmentManager::BeginPlay()
{
	Super::BeginPlay();
}


void UEquipmentManager::UpdateNewEquipmentToCapture(AItemBase* Equipment)
{
	if( APlayerCharacter* Player = Cast<APlayerCharacter>(GetOwner()) ) Player->GetEquipmentCaptureComponent()->ShowOnlyActorComponents(Equipment);
}

UEquipmentActorComponent* UEquipmentManager::GetEquipmentByType(EEquipmentType Type) const
{
	if( !EquipmentTypeToIndex.Contains(Type ) ) return nullptr;
	return EquipmentActors[EquipmentTypeToIndex[Type]].Get();
}

UEquipmentActorComponent* UEquipmentManager::GetEquipmentByClass(TSubclassOf<AItemBase> Class)
{
	for( auto& x: EquipmentActors)
	{
		if( x.IsValid() && x->GetChildActor() && x->GetChildActor()->IsA( Class ) ) return x.Get();
	}
	return nullptr;
}

UInventorySystem* UEquipmentManager::GetInventory() const
{
	return EquipmentInventory;
}

UEquipmentActorComponent* UEquipmentManager::CreateEquipment(UObject* Object, UMeshComponent* Mesh,
                                                             const FName& MeshSocketName,
                                                             const EEquipmentType EquipmentType)
{
	if( EquipmentTypeToIndex.Contains(EquipmentType) )
	{
		UE_LOG( LogTemp, Error, TEXT("%s is already exist"), *UEnum::GetValueAsName(EquipmentType).ToString() );
		return nullptr;
	}
	UEquipmentActorComponent* EquipmentActor = Object->CreateDefaultSubobject<UEquipmentActorComponent>( MeshSocketName );
	EquipmentActor->SetupAttachment( Mesh, MeshSocketName );
	EquipmentActor->EquipmentType = EquipmentType;
	EquipmentActor->EquipmentUpdateDelegate.AddUObject(this, &UEquipmentManager::UpdateNewEquipmentToCapture );
	AddEquipmentActorComponentToList(EquipmentActor);
	return EquipmentActor;
}

void UEquipmentManager::AddEquipmentActorComponentToList(UEquipmentActorComponent* Component)
{
	if( EquipmentTypeToIndex.Contains(Component->EquipmentType ))
	{
		UE_LOG( LogTemp, Error, TEXT("%s is already exist"), *UEnum::GetValueAsName(Component->EquipmentType).ToString() );
		return;
	}
	EquipmentTypeToIndex.Add( Component->EquipmentType, EquipmentActors.Num());
	EquipmentActors.Add(Component);
	if( EquipmentInventory )
	{
		if( Component->GetChildActor() )
		{
			AItemBase* Item = Cast<AItemBase>(Component->GetChildActor());
			EquipmentInventory->AddItem( Item->GetAsset(), 1);
		}
		else EquipmentInventory->AddEmpty();
		
	}
}
