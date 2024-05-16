// Fill out your copyright notice in the Description page of Project Settings.


#include "LimitedValue.h"

#include "Net/UnrealNetwork.h"


// Sets default values for this component's properties
ULimitedValue::ULimitedValue()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = false;
	// ...
}


void ULimitedValue::IncreaseCurrentValue(float Amount, bool Clamp)
{
	CurrentValue += Amount;
	if( Clamp ) CurrentValue = FMath::Clamp( CurrentValue, MinValue, MaxValue );
	if( CurrentValue >= MaxValue ) EventTriggerOnFull();
	else if( CurrentValue <= MinValue ) EventTriggerOnEmpty();
	Broadcast();
}

void ULimitedValue::DecreaseCurrentValue(float Amount, bool Clamp)
{
	IncreaseCurrentValue( -Amount, Clamp);
}

void ULimitedValue::SetValue(ELimitedValueFloatType Type, float Amount)
{
	GetValue( Type ) = Amount;
	Broadcast();
}

const float& ULimitedValue::GetValue(ELimitedValueFloatType Type) const
{
	switch (Type)
	{
	case Max:
		return MaxValue;
		break;
	case Min:
		return MinValue;
		break;
	case Current:
		return CurrentValue;
		break;
	}
	return CurrentValue;
}

void ULimitedValue::EventTriggerOnFull()
{
}

void ULimitedValue::EventTriggerOnEmpty()
{
}

float ULimitedValue::GetPercentage()
{
	return ( CurrentValue - MinValue ) / ( MaxValue - MinValue );
}

void ULimitedValue::GetPercent(float& Percent)
{
	Percent = GetPercentage();
}

// Called when the game starts
void ULimitedValue::BeginPlay()
{
	Super::BeginPlay();
	Broadcast();
	UpdateTimerHandle();
	
}


// Called every frame
void ULimitedValue::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);

}

float& ULimitedValue::GetValue(ELimitedValueFloatType Type)
{
	switch (Type)
	{
	case Max:
		return MaxValue;
		break;
	case Min:
		return MinValue;
		break;
	case Current:
		return CurrentValue;
		break;
	}
	return CurrentValue;
}

void ULimitedValue::SetStatusTimerType(EStatusTimerType Type)
{
	if( TimerType == Type ) return;
	TimerType = Type;
	if( PercentageTimePassHandle.IsValid() ) GetWorld()->GetTimerManager().ClearTimer( PercentageTimePassHandle );
	UpdateTimerHandle();
}

void ULimitedValue::UpdateTimerHandle()
{
	switch ( TimerType )
	{
	case EStatusTimerType::Decrease:
		GetWorld()->GetTimerManager().SetTimer(
			PercentageTimePassHandle,
			[&]()
			{
				if( TimerType == EStatusTimerType::Decrease )
				{
					DecreaseCurrentValue(DecreaseValueParams.Value);
				}
			},
			DecreaseValueParams.Period,
			true,
			DecreaseValueParams.Delay  );
			break;
	case EStatusTimerType::Increase:
		GetWorld()->GetTimerManager().SetTimer(
			PercentageTimePassHandle,
			[&]()
			{
				if( TimerType == EStatusTimerType::Increase )
				{
					IncreaseCurrentValue(IncreaseValueParams.Value);
				}
			},
			IncreaseValueParams.Period,
			true,
			DecreaseValueParams.Delay
		);
		break;
		default:
			break;
	}
}

void ULimitedValue::Broadcast()
{
	UpdatePercentageDelegate.Broadcast( GetPercentage() );
}

void ULimitedValue::OnRep_CurrentValue()
{
}

void ULimitedValue::GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const
{
	Super::GetLifetimeReplicatedProps(OutLifetimeProps);

	DOREPLIFETIME( ULimitedValue, CurrentValue);
}
