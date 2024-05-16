// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "EquipmentManager.generated.h"


class UInventorySystem;
class AItemBase;
class UEquipmentActorComponent;

UENUM(BlueprintType)
enum class EEquipmentType : uint8
{
	LeftHand,
	RightHand,
	UpperBody,
	LowerBody,
	Head,
	Num,
};

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UEquipmentManager : public UActorComponent
{
	GENERATED_BODY()

public:
	// Sets default values for this component's properties
	UEquipmentManager();


protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	TArray<TWeakObjectPtr<UEquipmentActorComponent>> EquipmentActors;
	
	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)
	UInventorySystem* EquipmentInventory;

	UPROPERTY()
	TMap<EEquipmentType, int32> EquipmentTypeToIndex;
	
	UFUNCTION()
	void UpdateNewEquipmentToCapture(AItemBase* Equipment);


public:
	UFUNCTION(BlueprintCallable)
	UEquipmentActorComponent* GetEquipmentByType(EEquipmentType Type) const;

	UFUNCTION(BlueprintCallable)
	UEquipmentActorComponent* GetEquipmentByClass(TSubclassOf<AItemBase> Class);
	
	UInventorySystem* GetInventory() const ;
	
	// only call this function in c++ constructor
	UEquipmentActorComponent* CreateEquipment(UObject* Object, UMeshComponent* Mesh, const FName& SocketString,
	                                          const EEquipmentType EquipmentType);

	// if you want to create equipment in blueprint, call this function
	UFUNCTION(BlueprintCallable)
	void AddEquipmentActorComponentToList(UEquipmentActorComponent* Component);
};
