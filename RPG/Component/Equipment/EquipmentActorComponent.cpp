// Fill out your copyright notice in the Description page of Project Settings.


#include "EquipmentActorComponent.h"

#include "GameFramework/Character.h"
#include "RPG/Interfaces/HasMontageComponent.h"


// Sets default values for this component's properties
UEquipmentActorComponent::UEquipmentActorComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	
	// ...
}

void UEquipmentActorComponent::SetEquipment_Implementation(TSubclassOf<AItemBase> EquipmentClass)
{
	AItemBase* Item = Cast<AItemBase>( GetChildActor() );
	// if current item has unequip anim, we equip new equipment after playing all unequip animation
	UMontageComponent* MontageComponent = IHasMontageComponent::Execute_GetMontageSystem( GetOwner() );
	if( MontageComponent && Item && Item->GetUnequipMontage() && Item->GetCharacterRef() )
	{
		Item->Unequip();
		FOnMontageEnded Delegate = FOnMontageEnded::CreateLambda( [&](UAnimMontage* Anim, bool bIsInterrupt) {
			// UE_LOG( LogTemp, Log, TEXT("%s %s"), *Anim->GetName(), EquipmentClass ? *EquipmentClass->GetName() : TEXT("nullptr") );
			EquipNewEquipment( EquipmentClass );
		});
		MontageComponent->GetAnimInstance()->Montage_SetEndDelegate(  Delegate, Item->GetUnequipMontage()  );
	}
	else
	{
		if( Item ) Item->Unequip();
		EquipNewEquipment( EquipmentClass );
	}
	
}


// Called when the game starts
void UEquipmentActorComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}

void UEquipmentActorComponent::EquipNewEquipment(TSubclassOf<AItemBase> EquipmentClass)
{
	DestroyChildActor();
	SetChildActorClass( EquipmentClass );
	CreateChildActor();
	AItemBase* NewEquipment = Cast<AItemBase>(GetChildActor() );
	EquipmentUpdateDelegate.Broadcast( NewEquipment );
	if( NewEquipment )
	{
		NewEquipment->SetActorHiddenInGame( NewEquipment->HiddenInGameWhenCreate() );
		if( NewEquipment->GetEquipMontage() ) NewEquipment->SetActorHiddenInGame( true );
		NewEquipment->Equip( Cast<ACharacter>(GetOwner() ), EquipmentType );
	}
}


// Called every frame
void UEquipmentActorComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                             FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

