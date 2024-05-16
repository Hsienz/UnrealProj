// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "EquipmentManager.h"
#include "Components/ChildActorComponent.h"
#include "RPG/Actor/ItemBase.h"
#include "EquipmentActorComponent.generated.h"


enum class EEquipmentType : uint8;
class AItemBase;
/*
 * @param: new equipment pointer
 */
DECLARE_MULTICAST_DELEGATE_OneParam( FEquipmentUpdateDelegate, AItemBase* );

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UEquipmentActorComponent : public UChildActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipmentActorComponent();

	UPROPERTY(BlueprintReadOnly,EditAnywhere)
	EEquipmentType EquipmentType;
	
	UFUNCTION(Server,Reliable)
	void SetEquipment(TSubclassOf<AItemBase> EquipmentClass );

	FEquipmentUpdateDelegate EquipmentUpdateDelegate;

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void EquipNewEquipment(TSubclassOf<AItemBase> EquipmentClass);
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
