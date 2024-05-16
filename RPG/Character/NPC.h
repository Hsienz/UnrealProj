// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "CharacterBase.h"
#include "GameFramework/Character.h"
#include "RPG/Interfaces/Interactable.h"
#include "NPC.generated.h"

UCLASS()
class RPG_API ANPC : public ACharacterBase, public IInteractable
{
	GENERATED_BODY()

	
public:
	// Sets default values for this character's properties
	ANPC();
	
protected:
	
	UPROPERTY(EditAnywhere,BlueprintReadWrite)
	TArray<FInteraction> Interactions;
	
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
/*
	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void InteractionTalk( AController* EventInstigator, AActor* Causer);

	UFUNCTION(BlueprintCallable,BlueprintNativeEvent)
	void InteractionBuy( AController* EventInstigator, AActor* Causer);
*/
	virtual TArray<FInteraction>& GetInteractions() override;
		
public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
};
