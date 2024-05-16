// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "NeedItemSlotWidget.h"
#include "Blueprint/UserWidget.h"
#include "RPG/PrimaryDataAssets/ItemPrimaryDataAsset.h"
#include "CraftMenu.generated.h"

class USlider;
class UCraftItemSelectionWidget;
class UScrollBox;
class UHorizontalBox;
class UButton;
class UNeedItemSlotWidget;
class APlayerCharacter;
struct FInventoryItem;
class UUniformGridPanel;
class UItemPrimaryDataAsset;
class UImage;
/**
 * 
 */
UCLASS()
class RPG_API UCraftMenu : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY( meta=(BindWidget))
	UImage* CraftTargetPreview;

	UPROPERTY( meta=(BindWidget))
	UHorizontalBox* NeedItemBox;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess) )
	TSubclassOf<UNeedItemSlotWidget> NeedItemSlotWidget;

	UPROPERTY( meta=( BindWidget ))
	UButton* CraftButton;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess) )
	TWeakObjectPtr<UItemPrimaryDataAsset> Asset;

	UPROPERTY( EditAnywhere, BlueprintReadOnly, meta=(AllowPrivateAccess) )
	TArray<UItemPrimaryDataAsset*> CraftableItems;

	UPROPERTY(meta=(BindWidget))
	UScrollBox* CraftableItemBox;

	UPROPERTY( BlueprintReadOnly, EditAnywhere, meta=(AllowPrivateAccess))
	TSubclassOf<UCraftItemSelectionWidget> CraftItemSelectionWidget;

	UPROPERTY( meta=(BindWidget))
	USlider* CraftAmountSliderBar;

	UPROPERTY(meta=(BindWidget))
	UTextBlock* CraftAmountText;

public:
	void UpdateAsset( UItemPrimaryDataAsset* NewAsset );
private:
	UFUNCTION()
	void Craft();

	UFUNCTION()
	FText SliderValueSyncToText();

	TArray<UCraftItemSelectionWidget*> PrepareCraftItemSelectionWidget();
protected:
	virtual void NativeConstruct() override;

	virtual bool Initialize() override;

};
