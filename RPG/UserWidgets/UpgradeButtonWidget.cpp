// Fill out your copyright notice in the Description page of Project Settings.


#include "UpgradeButtonWidget.h"

#include "ObjectOptionMenuWidget.h"
#include "RPG/Interfaces/UpgradeableObject.h"

void UUpgradeButtonWidget::HandleOnClick_Implementation()
{
	Super::HandleOnClick_Implementation();
	IUpgradeableObject* UpgradeableObject = Cast<IUpgradeableObject>(GetOwnerActor());
	if( UpgradeableObject )
	{
		UpgradeableObject->Upgrade();
	}
	else {
		UE_LOG( LogTemp, Log, TEXT("No interface IUpgradeableObject") );
	}
}
