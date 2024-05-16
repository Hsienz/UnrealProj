// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectOptionMenuButtonWidget.generated.h"

class UObjectOptionMenuWidget;
class UImage;
class UButton;
class UCanvasPanel;
/**
 * 
 */
UCLASS()
class RPG_API UObjectOptionMenuButtonWidget : public UUserWidget
{
	GENERATED_BODY()

	
public:
/*
	UPROPERTY( meta=(BindWidget) )
	UButton* Button;
*/

	void SetParentMenu( UObjectOptionMenuWidget* Menu );

	UObjectOptionMenuWidget* GetParentMenu();
	
	void SetAngle( float Angle );
	
	UPROPERTY( meta=(BindWidget))
	UImage* Icon;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite,meta=(BindWidget))
	UImage* Main;

	UPROPERTY( VisibleAnywhere, BlueprintReadWrite, meta=(BindWidget))
	UImage* Outer;
	
	UFUNCTION( BlueprintCallable, BlueprintNativeEvent )
	void HandleOnClick();

	void HandleOnSelect();

	void HandleOnUnselect();

	AActor* GetOwnerActor();

	
protected:
	virtual void NativeConstruct() override;
	TWeakObjectPtr<UObjectOptionMenuWidget> ParentMenu;

};

