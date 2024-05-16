// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "RPG/ActorComponents/LimitedValue/LimitedValue.h"
#include "StatusBarWidget.generated.h"

class ULimitedValue;
class UProgressBar;
/**
 * 
 */

UCLASS()
class RPG_API UStatusBarWidget : public UUserWidget
{
public:
	AActor* GetActorRef() const;
	void SetActorRef(AActor* Actor);

private:
	GENERATED_BODY()

	UPROPERTY(meta=(BindWidget))
	UProgressBar* ValueBar;

	UPROPERTY(EditAnywhere,BlueprintReadWrite,meta=(AllowPrivateAccess))
	ULimitedValue* Value;

	UPROPERTY(BlueprintReadWrite,EditAnywhere,meta=(AllowPrivateAccess))
	AActor* ActorRef;

public:
	UFUNCTION(BlueprintCallable)
	void SetValue( ULimitedValue* NewValue );
};


