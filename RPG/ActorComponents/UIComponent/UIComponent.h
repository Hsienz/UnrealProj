// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "UIComponent.generated.h"


class UWidget;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UUIComponent : public UActorComponent
{
	GENERATED_BODY()

protected:
	UPROPERTY(EditAnywhere,BlueprintReadOnly)
	TSubclassOf<UUserWidget> BP_Widget;

	UPROPERTY(VisibleAnywhere,BlueprintReadOnly)	
	TWeakObjectPtr<UUserWidget> WidgetPtr;

public:
	// Sets default values for this component's properties
	UUIComponent();
	
	UUserWidget* GetWidgetPtr() const;

	virtual bool CreateUI( bool InitShow = false);

	virtual void ShowUI();

	virtual void HideUI();

	virtual bool UpdateUI();

	virtual void ToggleUI();

	virtual bool DestroyUI();

	virtual void SetUIVisibility( ESlateVisibility Visibility);
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
