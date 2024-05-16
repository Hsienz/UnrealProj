// Fill out your copyright notice in the Description page of Project Settings.


#include "ItemBase.h"

#include "Components/PoseableMeshComponent.h"
#include "RPG/ActorComponents/Montage/MontageComponent.h"
#include "RPG/Character/PlayerCharacter.h"
#include "RPG/Component/Equipment/EquipmentActorComponent.h"


// Sets default values
AItemBase::AItemBase()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;
	bReplicates = true;
	
	RootSceneComponent = CreateDefaultSubobject<USceneComponent>(TEXT("RootComponent"));
	RootComponent = RootSceneComponent;

	StaticMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("StaticMesh"));
	StaticMesh->SetCollisionProfileName( "NoCollision" );
	StaticMesh->SetupAttachment( RootComponent);

	PoseableMesh = CreateDefaultSubobject<UPoseableMeshComponent>(TEXT("PoseableMesh"));
	PoseableMesh->SetCollisionProfileName( "NoCollision");
	PoseableMesh->SetupAttachment( RootComponent);

}

UItemPrimaryDataAsset* AItemBase::GetAsset()
{
	return Asset;
}

// Called when the game starts or when spawned
void AItemBase::BeginPlay()
{
	Super::BeginPlay();
}

void AItemBase::PostInitializeComponents()
{
	Super::PostInitializeComponents();
	InitMeshType();
}

void AItemBase::InitMeshType()
{
	switch (MeshType)
	{
	case EMeshType::Static:
		StaticMesh->SetVisibility( true );
		PoseableMesh->SetVisibility(false);
		break;
	case EMeshType::Poseable:
		StaticMesh->SetVisibility(false);
		PoseableMesh->SetVisibility(true);
		break;
	}
}

// Called every frame
void AItemBase::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

void AItemBase::RightUse_Implementation()
{
}

void AItemBase::LeftUse_Implementation()
{
}


void AItemBase::Equip(ACharacter* Character, EEquipmentType Type)
{
	CharacterRef = Character;
	TryPlayEquipMontage();
}

void AItemBase::Unequip()
{
	if( !UnequipMontage ) Destroy();
	else TryPlayUnequipMontage();
	CharacterRef = nullptr;
}

UAnimInstance* AItemBase::GetAnimInstance() const
{
	if( CharacterRef.IsValid() )
	{
		return CharacterRef->GetMesh()->GetAnimInstance();
	}
	return nullptr;
}

ACharacter* AItemBase::GetCharacterRef() const
{
	return CharacterRef.IsValid() ? CharacterRef.Get() : nullptr;
}

void AItemBase::SetCharacterRef(ACharacter* OwnerCharacter) 
{
	CharacterRef = OwnerCharacter;
}

UMeshComponent* AItemBase::GetMesh()
{
	switch (MeshType)
	{
	case EMeshType::Static:
		return StaticMesh;
	case EMeshType::Poseable:
		return PoseableMesh;
	}
	return nullptr;
}

void AItemBase::TryPlayEquipMontage()
{
	if( !EquipMontage || !CharacterRef.IsValid() ) return;
	UMontageComponent* MontageComponent = IHasMontageComponent::Execute_GetMontageSystem( CharacterRef.Get());
	if( !MontageComponent ) return;
	MontageComponent->GetAnimInstance()->Montage_Stop( 2, UnequipMontage );
	MontageComponent->ServerMulticastMontagePlay( EquipMontage );
	MontageComponent->GetAnimInstance()->OnPlayMontageNotifyBegin.AddUniqueDynamic( this, &AItemBase::PlayEquipmentMontageNotifyBegin );
}

void AItemBase::PlayEquipmentMontageNotifyBegin(const FName NotifyName,
	const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	BranchingPointPayload.SkelMeshComponent->GetAnimInstance()->OnPlayMontageNotifyBegin.RemoveDynamic( this, &AItemBase::PlayEquipmentMontageNotifyBegin );
}

void AItemBase::TryPlayUnequipMontage()
{
	if( !EquipMontage || !CharacterRef.IsValid() ) return;
	UMontageComponent* MontageComponent = IHasMontageComponent::Execute_GetMontageSystem( CharacterRef.Get());
	if( !MontageComponent ) return;
	MontageComponent->GetAnimInstance()->Montage_Stop( 2, EquipMontage );
	MontageComponent->ServerMulticastMontagePlay( UnequipMontage );
	MontageComponent->GetAnimInstance()->OnPlayMontageNotifyBegin.AddUniqueDynamic( this, &AItemBase::PlayUnequipmentMontageNotifyBegin );
}

void AItemBase::PlayUnequipmentMontageNotifyBegin(const FName NotifyName,
	const FBranchingPointNotifyPayload& BranchingPointPayload)
{
	BranchingPointPayload.SkelMeshComponent->GetAnimInstance()->OnPlayMontageNotifyBegin.RemoveDynamic( this, &AItemBase::PlayUnequipmentMontageNotifyBegin );
}




