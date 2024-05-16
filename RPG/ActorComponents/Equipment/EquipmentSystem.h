// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPG/ActorComponents/IMCActorComponent.h"
#include "EquipmentSystem.generated.h"


class UEquipmentManager;
class AItemBase;

enum class EEquipmentInputActionType
{
	Left,
	Right
};

class UInputAction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UEquipmentSystem : public UIMCActorComponent
{
	GENERATED_BODY()

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess))
	UInputAction* Left;

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UInputAction* Right;

	// we are trying to use item in EquipmentManager
	TWeakObjectPtr<UEquipmentManager> EquipmentManagerRef;


	
public:
	// Sets default values for this component's properties
	UEquipmentSystem();

	UInputAction* GetInputAction(EEquipmentInputActionType Type) const;
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void InitializeComponent() override;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	UFUNCTION(BlueprintCallable,Server,Reliable)
	void RPC_LeftUse();

	UFUNCTION(BlueprintCallable,Server,Reliable)
	void RPC_RightUse();

	UFUNCTION(BlueprintCallable,Server,Reliable)
	void RPC_RightRelease();
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
