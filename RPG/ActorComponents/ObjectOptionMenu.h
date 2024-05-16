// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "ObjectOptionMenu.generated.h"


class UObjectOptionMenuButtonWidget;
class UObjectOptionMenuWidget;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UObjectOptionMenu : public UActorComponent
{
	GENERATED_BODY()

public:	
	// Sets default values for this component's properties
	UObjectOptionMenu();

	UPROPERTY( EditAnywhere, BlueprintReadWrite, Category="Menu")
	TSubclassOf<UObjectOptionMenuWidget> Menu;

	TWeakObjectPtr<UObjectOptionMenuWidget> ObjectOptionMenuWidget;
	
	void OpenMenu();

	void CloseMenu();

	// void ToggleMenu();

	void ClickMenuButton();
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
