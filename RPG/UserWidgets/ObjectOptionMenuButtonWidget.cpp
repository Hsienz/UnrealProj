// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectOptionMenuButtonWidget.h"

#include "ObjectOptionMenuWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/Button.h"
#include "Components/Image.h"

void UObjectOptionMenuButtonWidget::HandleOnClick_Implementation()
{
	UE_LOG( LogTemp, Log, TEXT("Button Click"));
}

void UObjectOptionMenuButtonWidget::HandleOnSelect()
{
	Outer->SetVisibility( ESlateVisibility::Visible );
}

void UObjectOptionMenuButtonWidget::HandleOnUnselect()
{
	Outer->SetVisibility( ESlateVisibility::Hidden );
}

AActor* UObjectOptionMenuButtonWidget::GetOwnerActor()
{
	if( ParentMenu.IsValid() ) return ParentMenu->GetOwnerActor();
	return nullptr;
}


void UObjectOptionMenuButtonWidget::NativeConstruct()
{
	Super::NativeConstruct();
	// Button->OnClicked.AddDynamic(this, &UObjectOptionMenuButtonWidget::HandleOnClick );
	
}


void UObjectOptionMenuButtonWidget::SetAngle(float Angle)
{
	Outer->GetDynamicMaterial()->SetScalarParameterValue("Angle", Angle );
	Main->GetDynamicMaterial()->SetScalarParameterValue("Angle",Angle);
}

void UObjectOptionMenuButtonWidget::SetParentMenu(UObjectOptionMenuWidget* Menu)
{
	ParentMenu = Menu;
}

UObjectOptionMenuWidget* UObjectOptionMenuButtonWidget::GetParentMenu()
{
	return ParentMenu.Get();
}
