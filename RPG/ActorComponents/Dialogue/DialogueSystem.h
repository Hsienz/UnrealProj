// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Components/ActorComponent.h"
#include "RPG/ActorComponents/IMCActorComponent.h"
#include "DialogueSystem.generated.h"


class UDialogueBox;
class UInputAction;

UCLASS(ClassGroup=(Custom), meta=(BlueprintSpawnableComponent))
class RPG_API UDialogueSystem : public UIMCActorComponent
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere,BlueprintReadOnly,meta=(AllowPrivateAccess))
	UInputAction* ToNextDialogueAction;

	TWeakObjectPtr<UDialogueBox> DialogueBoxRef;
	
public:
	// Sets default values for this component's properties
	UDialogueSystem();

protected:
	// Called when the game starts
	virtual void BeginPlay() override;

	UFUNCTION()
	void ToNextDialogue();
public:
	// Called every frame
	virtual void TickComponent(float DeltaTime, ELevelTick TickType,
	                           FActorComponentTickFunction* ThisTickFunction) override;

	virtual void SetupPlayerInputComponent(UInputComponent* PlayerInputComponent) override;
};
