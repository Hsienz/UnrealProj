// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentSystem.h"

#include "EnhancedInputComponent.h"
#include "RPG/Actor/ItemBase.h"
#include "RPG/Actor/Shield.h"
#include "RPG/Character/PlayerCharacter.h"
#include "RPG/Component/Equipment/EquipmentActorComponent.h"
#include "RPG/Component/Equipment/EquipmentManager.h"


// Sets default values for this component's properties
UEquipmentSystem::UEquipmentSystem()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	bWantsInitializeComponent = true;
	// ...
}

UInputAction* UEquipmentSystem::GetInputAction(EEquipmentInputActionType Type) const
{
	switch (Type)
	{
	case EEquipmentInputActionType::Left:
		return Left;
	case EEquipmentInputActionType::Right:
		return Right;
	}
	return nullptr;
}


// Called when the game starts
void UEquipmentSystem::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UEquipmentSystem::InitializeComponent()
{
	Super::InitializeComponent();
	// EquipmentManagerRef = Cast<IHasEquipmentManager>( GetOwner() )->Execute_GetEquipmentManager();
	EquipmentManagerRef = IHasEquipmentManager::Execute_GetEquipmentManager( GetOwner() );
}

void UEquipmentSystem::RPC_RightRelease_Implementation()
{
	if( EquipmentManagerRef.IsValid() )
	{
		AActor* LeftHandActor = EquipmentManagerRef->GetEquipmentByType(EEquipmentType::LeftHand)->GetChildActor();
		if( AShield* Shield = Cast<AShield>(LeftHandActor) )
		{
			Shield->RightRelease();
		}
	}
}

void UEquipmentSystem::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	if( UEnhancedInputComponent* EnhancedInputComponent = Cast<UEnhancedInputComponent>(PlayerInputComponent) )
	{
		EnhancedInputComponent->BindAction( Left, ETriggerEvent::Started, this, &UEquipmentSystem::RPC_LeftUse );

		EnhancedInputComponent->BindAction( Right, ETriggerEvent::Started, this, &UEquipmentSystem::RPC_RightUse );
		EnhancedInputComponent->BindAction( Right, ETriggerEvent::Completed, this, &UEquipmentSystem::RPC_RightRelease );
	}
}


// Called every frame
void UEquipmentSystem::TickComponent(float DeltaTime, ELevelTick TickType,
                                     FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}


void UEquipmentSystem::RPC_LeftUse_Implementation()
{
	if( EquipmentManagerRef.IsValid())
	{
		if( AItemBase* ItemBase = Cast<AItemBase>( EquipmentManagerRef->GetEquipmentByType(EEquipmentType::RightHand)->GetChildActor())) ItemBase->LeftUse();
	}
}

void UEquipmentSystem::RPC_RightUse_Implementation()
{
	if( EquipmentManagerRef.IsValid() )
	{
		AActor* LeftHandActor = EquipmentManagerRef->GetEquipmentByType(EEquipmentType::LeftHand)->GetChildActor();
		if( AShield* Shield = Cast<AShield>( LeftHandActor ) )
		{
			Shield->RightUse();
		}
	}
}
