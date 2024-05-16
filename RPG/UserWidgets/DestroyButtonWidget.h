// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "ObjectOptionMenuButtonWidget.h"
#include "DestroyButtonWidget.generated.h"

/**
 * 
 */
UCLASS()
class RPG_API UDestroyButtonWidget : public UObjectOptionMenuButtonWidget
{
	GENERATED_BODY()
public:
	virtual void HandleOnClick_Implementation() override;
};
