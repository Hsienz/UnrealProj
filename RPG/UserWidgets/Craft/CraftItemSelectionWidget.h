// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPG/PrimaryDataAssets/ItemPrimaryDataAsset.h"
#include "CraftItemSelectionWidget.generated.h"

class UButton;
class UImage;
class UTextBlock;
class UItemPrimaryDataAsset;
/**
 * 
 */

DECLARE_DELEGATE_OneParam(FOnButtonClick, UItemPrimaryDataAsset* );

UCLASS()
class RPG_API UCraftItemSelectionWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere, meta=(AllowPrivateAccess) )
	UItemPrimaryDataAsset* Asset;

	UPROPERTY(meta=(BindWidget))
	UImage* ItemIcon;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* ItemName;

	UPROPERTY(meta=(BindWidget))
	UButton* Button;

	bool bIsCraftable;
public:
	void UpdateAsset( UItemPrimaryDataAsset* NewAsset );
	
	FOnButtonClick OnButtonClick;

	bool IsCraftable() const ;

	UItemPrimaryDataAsset* GetAsset() const ; 

	bool operator<( const UCraftItemSelectionWidget& Other ) const;
private:
	UFUNCTION()
	void OnClick();
protected:
	virtual void NativeConstruct() override;
};
