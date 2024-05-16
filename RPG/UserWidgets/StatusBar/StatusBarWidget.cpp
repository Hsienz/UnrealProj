// Fill out your copyright notice in the Description page of Project Settings.


#include "StatusBarWidget.h"

#include "RPG/ActorComponents/LimitedValue/LimitedValue.h"
#include "Components/ProgressBar.h"
#include "Components/WidgetComponent.h"
#include "RPG/Character/Enemy.h"


AActor* UStatusBarWidget::GetActorRef() const
{
	return ActorRef;
}

void UStatusBarWidget::SetActorRef(AActor* Actor)
{
	this->ActorRef = Actor;
}

void UStatusBarWidget::SetValue(ULimitedValue* NewValue)
{
	Value = NewValue;
	if( Value )
	{
		Value->UpdatePercentageDelegate.AddLambda(  [&]( float Percentage )
		{
			ValueBar->SetPercent( Percentage );
		});
		
	}
	Value->Broadcast();
}
