// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyButtonWidget.h"

#include "ObjectOptionMenuWidget.h"

void UDestroyButtonWidget::HandleOnClick_Implementation()
{
	Super::HandleOnClick_Implementation();
	GetOwnerActor()->Destroy();
}
