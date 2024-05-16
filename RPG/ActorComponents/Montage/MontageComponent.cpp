// Fill out your copyright notice in the Description page of Project Settings.


#include "MontageComponent.h"

#include "GameFramework/Character.h"


// Sets default values for this component's properties
UMontageComponent::UMontageComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	SetIsReplicatedByDefault(true);
	// ...
}


// Called when the game starts
void UMontageComponent::BeginPlay()
{
	Super::BeginPlay();

	// ...
	
}


// Called every frame
void UMontageComponent::TickComponent(float DeltaTime, ELevelTick TickType,
                                      FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

	// ...
}

void UMontageComponent::ServerMulticastMontagePlay_Implementation(
	UAnimMontage* Montage,
	float InPlayRate,
	EMontagePlayReturnType ReturnValueType,
	float InTimeToStartMontageAt, bool bStopAllMontage)
{
	MulticastMontagePlay(  Montage, InPlayRate, ReturnValueType, InTimeToStartMontageAt, bStopAllMontage);
}

void UMontageComponent::MulticastMontagePlay_Implementation(
	UAnimMontage* Montage,
	float InPlayRate,
	EMontagePlayReturnType ReturnValueType,
	float InTimeToStartMontageAt, bool bStopAllMontage
)
{
	MontagePlay(  Montage, InPlayRate, ReturnValueType, InTimeToStartMontageAt, bStopAllMontage);
}

float UMontageComponent::MontagePlay(
	UAnimMontage* Montage,
	float InPlayRate,
	EMontagePlayReturnType ReturnValueType,
	float InTimeToStartMontageAt, bool bStopAllMontage
)
{
	if( ACharacter* Owner = Cast<ACharacter>(GetOwner()) )
	{
		return Owner->GetMesh()->GetAnimInstance()->Montage_Play(
		Montage,
		InPlayRate,
		ReturnValueType,
		InTimeToStartMontageAt,
		bStopAllMontage
		);
	}
	return 0;
}

UAnimInstance* UMontageComponent::GetAnimInstance() const
{
	if( ACharacter* Owner = Cast<ACharacter>(GetOwner())) {
		return Owner->GetMesh()->GetAnimInstance();
	}
	return nullptr;
}
