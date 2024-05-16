// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IMCActorComponent.h"
#include "Components/ActorComponent.h"
#include "ObjectOptionMenuSystem.generated.h"


class UObjectOptionMenu;
class UObjectOptionMenuWidget;
class UInputAction;

UCLASS( ClassGroup=(Custom), meta=(BlueprintSpawnableComponent) )
class RPG_API UObjectOptionMenuSystem : public UIMCActorComponent
{
	GENERATED_BODY()

	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess))
	UInputAction* OpenObjectOptionMenuAction;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess))
	UInputAction* CloseObjectOptionMenuAction;
	
	UPROPERTY( EditDefaultsOnly, BlueprintReadOnly, Category="Input", meta=(AllowPrivateAccess))
	UInputAction* ClickOnMenuButtonAction;

public:	
	// Sets default values for this component's properties
	UObjectOptionMenuSystem();

	void AttemptOpenObjectOptionMenu();

	void CloseObjectOptionMenu();

	void ToggleObjectOptionMenu();

	void ClickMenuButton();
	
protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;

private:
	TWeakObjectPtr<UObjectOptionMenu> LastestOpenMenu;
	
public:	
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction) override;

		
};
