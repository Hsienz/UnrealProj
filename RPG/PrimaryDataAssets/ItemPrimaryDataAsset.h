// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "RPG/Struct/Craft/CraftRecipe.h"
#include "Engine/DataAsset.h"
#include "ItemPrimaryDataAsset.generated.h"

struct FCraftRecipe;
struct FInventoryItem;
/**
 * 
 */
UCLASS()
class RPG_API UItemPrimaryDataAsset : public UPrimaryDataAsset
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere)
	FText ItemText;
	
	UPROPERTY(EditAnywhere)
	FName ItemName;

	UPROPERTY(EditAnywhere)
	FText ItemDescription;

	UPROPERTY(EditAnywhere)
	UTexture2D* ItemThumbnail;

	UPROPERTY(EditAnywhere)
	UStaticMesh* ItemMesh;
	
	UPROPERTY(EditAnywhere)
	USkeletalMesh* ItemSkeletalMesh;
	
	UPROPERTY(EditAnywhere)
	int32 MaxStack = 1;

	UPROPERTY(EditAnywhere)
	FCraftRecipe CraftRecipe;

	UPROPERTY(EditAnywhere)
	TObjectPtr<UClass> ItemClass;
	
public:
	const FText& GetItemText() const;

	const FName& GetItemName() const ;

	const FText& GetItemDescription() const ;

	UTexture2D* GetItemThumbnail() const;

	UStaticMesh* GetItemStaticMesh() const;

	USkeletalMesh* GetItemSkeletalMesh() const;

	TObjectPtr<UClass> GetItemClass() const;
	
	int32 GetMaxStack() const ;

	const FCraftRecipe& GetCraftRecipe() const;

	int32 GetMaxCraftNum(UInventorySystem* Inventory) ;
	
	bool IsCraftable( UInventorySystem* InventorySystem ) const ;
	
	bool IsEnoughOnCertainItem( const FInventoryItem* Slot ) const;

	void Craft( UInventorySystem* InventorySystem ) ;
};
