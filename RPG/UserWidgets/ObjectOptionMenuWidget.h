// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "ObjectOptionMenuWidget.generated.h"

class UCanvasPanel;
class UObjectOptionMenuButtonWidget;
/**
 * 
 */
UCLASS()
class RPG_API UObjectOptionMenuWidget : public UUserWidget
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category="Button", meta=(AllowPrivateAccess) )
	TArray<TSubclassOf<UObjectOptionMenuButtonWidget>> ObjectOptionMenuButtonWidgets;

	UPROPERTY(meta=(BindWidget))
	UCanvasPanel* ObjectOptionMenuCanvas;


	FVector2d OriginLocation;

	int8 CurrentActiveButtonIndex = -1;

	float ButtonAngle;
	

public:
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadWrite )
	float DistanceSquareThreshold = 40000;
	
	virtual void NativeTick(const FGeometry& MyGeometry, float InDeltaTime) override;

	void SetOwnerActor( AActor* Actor );

	AActor* GetOwnerActor();

	void ClickActiveButton();
	
	virtual void RemoveFromParent() override;
protected:
	
	virtual void NativeConstruct() override;
	
private:
	
	void SelectClosestButton( float Angle );

	float CalcAngleFromOrigin();

	TWeakObjectPtr<AActor> OwnerActor;
};
