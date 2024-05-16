// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CollisionTriggerComponent.h"
#include "InteractionHintCollision.generated.h"


class UHintWidget;
class IInteractable;
class UInteractableHintBoxWidget;

USTRUCT()
struct FInteractableActorRecord
{
	GENERATED_BODY()


	TArray<UHintWidget*> HintWidgets;
};


UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UInteractionHintCollision : public UCollisionTriggerComponent
{
	GENERATED_BODY()

	TWeakObjectPtr<UInteractableHintBoxWidget> InteractableHintBoxWidgetPtr;

	UPROPERTY()
	TMap<AActor*, FInteractableActorRecord> InteractableActorBelongingHintWidget;
public:
	// Sets default values for this component's properties
	UInteractionHintCollision();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	virtual void OnCollisionBegin_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult) override;

	virtual void OnCollisionEnd_Implementation(UPrimitiveComponent* OverlappedComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex) override;

public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;
};
