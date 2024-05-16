// Fill out your copyright notice in the Description page of Project Settings.


#include "ObjectOptionMenuWidget.h"

#include "ObjectOptionMenuButtonWidget.h"
#include "Blueprint/WidgetLayoutLibrary.h"
#include "Components/CanvasPanel.h"
#include "Components/CanvasPanelSlot.h"

void UObjectOptionMenuWidget::NativeTick(const FGeometry& MyGeometry, float InDeltaTime)
{
	Super::NativeTick(MyGeometry, InDeltaTime);
	float Angle = CalcAngleFromOrigin();
	SelectClosestButton( Angle );
}

void UObjectOptionMenuWidget::SetOwnerActor(AActor* Actor)
{
	OwnerActor = Actor;
}

AActor* UObjectOptionMenuWidget::GetOwnerActor()
{
	return OwnerActor.Get();
}

void UObjectOptionMenuWidget::ClickActiveButton()
{
	if( CurrentActiveButtonIndex != -1 )
	{
		UWidget* Widget = ObjectOptionMenuCanvas->GetChildAt( CurrentActiveButtonIndex );
		if( !Widget )
		{
			UE_LOG( LogTemp, Warning , TEXT("Widget is null"));
		}
		else
		{
			UObjectOptionMenuButtonWidget* ButtonWidget = Cast<UObjectOptionMenuButtonWidget>( Widget );
			if( !ButtonWidget )
			{
				UE_LOG( LogTemp, Warning, TEXT("ButtonWidget is null"));
			}
			else
			{
				ButtonWidget->HandleOnClick();
			}
		}
	}
}

void UObjectOptionMenuWidget::NativeConstruct()
{
	Super::NativeConstruct();
	int8 Num = ObjectOptionMenuButtonWidgets.Num();

	ButtonAngle = 360. / Num;
	
	for( int8 i = 0; i < Num; i++ )
	{
		UObjectOptionMenuButtonWidget* Widget = CreateWidget<UObjectOptionMenuButtonWidget>( this, ObjectOptionMenuButtonWidgets[i] );
		Widget->SetParentMenu( this );
		Widget->SetAngle( ButtonAngle / 360 );
		UCanvasPanelSlot* CanvasPanelSlot= Cast<UCanvasPanelSlot>( ObjectOptionMenuCanvas->AddChild( Widget ) );
		float Angle = 360. * i / Num;
		Widget->SetRenderTransformAngle( Angle );
		Widget->SetRenderScale(FVector2D(2.));
		CanvasPanelSlot->SetAnchors( FAnchors(.5) );
		CanvasPanelSlot->SetAlignment( FVector2D(.5) );
		CanvasPanelSlot->SetPosition( FVector2D(0) );
		
	}

	OriginLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	GetWorld()->GetFirstPlayerController()->SetInputMode( FInputModeGameAndUI() );
}

void UObjectOptionMenuWidget::RemoveFromParent()
{
	if( GetWorld() && GetWorld()->GetFirstPlayerController() )
		GetWorld()->GetFirstPlayerController()->SetInputMode( FInputModeGameOnly() );
	Super::RemoveFromParent();
}


float UObjectOptionMenuWidget::CalcAngleFromOrigin()
{
	FVector2d CurrentMouseLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	FVector2d NormalizedOriginToCurrentMouseLocation = ( CurrentMouseLocation-OriginLocation ).GetSafeNormal();
	float CosRadian = FVector2d::DotProduct(FVector2d(0,-1), NormalizedOriginToCurrentMouseLocation );
	float Radian = FMath::Acos( CosRadian );
	float Angle = FMath::RadiansToDegrees( Radian );
	if(  NormalizedOriginToCurrentMouseLocation.X < 0 ) Angle = 360 - Angle;
	return Angle;
}


void UObjectOptionMenuWidget::SelectClosestButton(float Angle)
{
	int ToActiveButtonIndex = static_cast<int>( Angle + ButtonAngle / 2 ) % 360 / ButtonAngle ;
	FVector2d CurrentMouseLocation = UWidgetLayoutLibrary::GetMousePositionOnViewport(GetWorld());
	float DistanceSquare = FVector2d::DistSquared( OriginLocation, CurrentMouseLocation );
	if( DistanceSquare < DistanceSquareThreshold ) ToActiveButtonIndex = -1;
	if( ToActiveButtonIndex != CurrentActiveButtonIndex ) {
		if( CurrentActiveButtonIndex != -1 )
		{
			Cast<UObjectOptionMenuButtonWidget>(ObjectOptionMenuCanvas->GetChildAt( CurrentActiveButtonIndex ))->HandleOnUnselect();
		}
		if( ToActiveButtonIndex != -1 ) Cast<UObjectOptionMenuButtonWidget>(ObjectOptionMenuCanvas->GetChildAt(ToActiveButtonIndex))->HandleOnSelect();
		CurrentActiveButtonIndex = ToActiveButtonIndex;
	}
}

