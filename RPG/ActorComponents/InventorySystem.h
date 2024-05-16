// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IMCActorComponent.h"
#include "RPG/Struct/ItemSlot.h"
#include "Components/ActorComponent.h"
#include "InventorySystem.generated.h"

struct FInventoryItem;
class AItemBase;
class UUIInventoryComponent;
class UInputAction;
class UInventoryMenu;
class UWidget;
class UInventoryItemSlotWidget;
struct FDropItem;
class UItemPrimaryDataAsset;


UENUM()
enum class EInventorySearchMethod
{
	First,
	FirstNotFull
};


using FInventory = TArray<FInventoryItem>;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UInventorySystem : public UIMCActorComponent
{
	GENERATED_BODY()
	
	TWeakObjectPtr<UUIInventoryComponent> UIInventoryRef;
	
	UPROPERTY( BlueprintReadOnly, EditAnywhere, meta=(AllowPrivateAccess))
	UInputAction* OpenMenuAction;
	
	UPROPERTY( EditAnywhere, BlueprintReadWrite, meta=(AllowPrivateAccess) )
	TArray<FInventoryItem> Inventory;

public:
	// Sets default values for this component's properties
	UInventorySystem();

	void AddItem( UItemPrimaryDataAsset* Item, int32 Amount );

	void AddItem(  const FDropItem& DropItem );

	void AddItem( const FInventoryItem& ItemSlot );

	void AddEmpty( int32 Amount = 1);

	TSharedPtr<FInventoryItem> GetNotFullInventorySlot(UItemPrimaryDataAsset* Item);

	int32 GetInventorySlotIndex( UItemPrimaryDataAsset* Item, EInventorySearchMethod Method = EInventorySearchMethod::First );

	int32 GetNotFullInventorySlotIndex( UItemPrimaryDataAsset* Item );

	int32 GetItemAmount( UItemPrimaryDataAsset* Item );

	void RemoveItemAmount( UItemPrimaryDataAsset* Item, int32 Amount );

	TSharedPtr<FInventoryItem> GetInventorySlot(UItemPrimaryDataAsset* Item,
	                                            EInventorySearchMethod Method = EInventorySearchMethod::First);

	TArray<FInventoryItem>& GetInventory();

	TSharedRef<FInventoryItem> GetInventoryItem( int32 Index );

	UFUNCTION()
	void ToggleInventoryMenu();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;


	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

	FInventoryItem operator[] (int32 Index) const;

	FInventoryItem& operator[] (int32 Index);
};
