// Fill out your copyright notice in the Description page of Project Settings.


#include "ActionWrapper.h"

void UActionLibrary::StartCooldown(FActionWrapper& Action)
{
	if( Action.CooldownTime <= 0 ) return;
	Action.bIsCooldown = true;
}

void UActionLibrary::CountdownCooldown(UWorld* Context, FActionWrapper& Action)
{
	if( Action.CooldownTime <= 0 ) return;
	FTimerDelegate Delegate = FTimerDelegate::CreateLambda( [&]()
	{
		Action.bIsCooldown = false;
	} );
	Context->GetTimerManager().SetTimer( Action.CooldownTimerHandle, Delegate, Action.CooldownTime, false );
}

void UActionLibrary::StartAndCountdownCooldown(UWorld* Context, FActionWrapper& Action)
{
	StartCooldown( Action );
	CountdownCooldown(Context, Action);
}

