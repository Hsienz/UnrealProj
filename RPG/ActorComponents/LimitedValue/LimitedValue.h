// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "Components/ProgressBar.h"
#include "Components/TextBlock.h"
#include "LimitedValue.generated.h"

class UTextBlock;
class UProgressBar;
DECLARE_MULTICAST_DELEGATE_OneParam(FUpdatePercentage, float );


UENUM()
enum ELimitedValueFloatType
{
	Max,
	Min,
	Current
};

USTRUCT(BlueprintType)
struct FAdjustValueParams
{
	GENERATED_BODY()

public:
	UPROPERTY(EditAnywhere)
	float Delay;

	UPROPERTY(EditAnywhere)
	float Period;

	UPROPERTY(EditAnywhere)
	float Value;
};


UENUM(BlueprintType)
enum class EStatusTimerType : uint8
{
	None,
	Decrease,
	Increase,
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API ULimitedValue : public UActorComponent
{
	GENERATED_BODY()
	UPROPERTY( BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess) )
	float MinValue;

	UPROPERTY( BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess) )
	float MaxValue = 1;

	UPROPERTY( BlueprintReadWrite, EditAnywhere, meta=(AllowPrivateAccess), ReplicatedUsing=OnRep_CurrentValue)
	float CurrentValue;
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool DecreaseByTime = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess, EditCondition="DecreaseByTime", EditConditionHides))
	FAdjustValueParams DecreaseValueParams;

	UPROPERTY(EditAnywhere,BlueprintReadWrite, meta=(AllowPrivateAccess))
	bool IncreaseByTime = false;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess, EditCondition="IncreaseByTime", EditConditionHides))
	FAdjustValueParams IncreaseValueParams;

	FTimerHandle PercentageTimePassHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite,meta=(AllowPrivateAccess))
	EStatusTimerType TimerType;
	
	
public:
	
	// Sets default values for this component's properties
	ULimitedValue();

	
	void IncreaseCurrentValue( float Amount, bool Clamp = true);

	void DecreaseCurrentValue( float Amount, bool Clamp = true );

	void SetValue( ELimitedValueFloatType Type, float Amount );

	const float& GetValue(ELimitedValueFloatType Type) const ;
	float& GetValue( ELimitedValueFloatType Type );

	virtual void EventTriggerOnFull();

	virtual void EventTriggerOnEmpty();

	float GetPercentage();
	
	UFUNCTION(BlueprintCallable)
	void GetPercent(float& Percent );

	void SetStatusTimerType( EStatusTimerType Type );
	
	void UpdateTimerHandle();

	FUpdatePercentage UpdatePercentageDelegate;

	void Broadcast();

	UFUNCTION()
	virtual void OnRep_CurrentValue();
private:
	void UpdatePercentage( UProgressBar* ProgressBar, UTextBlock* Text );
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;


	virtual void GetLifetimeReplicatedProps(TArray<FLifetimeProperty>& OutLifetimeProps) const override;

	
};
