// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "HintWidget.generated.h"

class UHintBoxWidget;
class IInteractable;
class UImage;
class UTextBlock;
/**
 * 
 */
UCLASS()
class RPG_API UHintWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	UTextBlock* HintText;

	UPROPERTY(meta=(BindWidget))
	UImage* HintIcon;

	TWeakObjectPtr<UUserWidget> ParentWidgetRef;
	
public:
	UUserWidget* GetParentWidgetRef() const;

	void SetParentWidgetRef(UUserWidget* ParentWidget);

	virtual void SetHintText(FText Text);

	void SetHintIcon( UTexture2D* Texture);
};
