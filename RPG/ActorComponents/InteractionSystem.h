// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "IMCActorComponent.h"
#include "InteractionSystem.generated.h"


class UInteractableHintBoxWidget;
class UHintBoxWidget;
class UHintWidget;
class AFoliageActor;
class UInputAction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UInteractionSystem : public UIMCActorComponent
{
	GENERATED_BODY()

	UPROPERTY(BlueprintReadOnly, EditAnywhere,meta=(AllowPrivateAccess))
	UInputAction* InteractionAction;

	TWeakObjectPtr<UInteractableHintBoxWidget> InteractableHintBoxWidgetPtr;
	
public:
	// Sets default values for this component's properties
	UInteractionSystem();

	void HandleInteraction();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	void FrontTrace();
private:
	
	FHitResult HitResult;
	bool bIsHit;
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
