// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerHUD.h"
#include "Blueprint/UserWidget.h"

APlayerHUD::APlayerHUD()
{
	static ConstructorHelpers::FClassFinder<UTexture2D> HealthBarObj(TEXT
	("/Content/UI/Health_UI"));

	HUDWidgetClass = HealthBarObj.Class;
}

void APlayerHUD::DrawHUD()
{
	Super::DrawHUD();


}

void APlayerHUD::BeginPlay()
{
	Super::BeginPlay();

	if (HUDWidgetClass != nullptr)
	{
		CurrentWidget = CreateWidget<UUserWidget>(GetWorld(), HUDWidgetClass);

		if (CurrentWidget)
		{
			CurrentWidget->AddToViewport();
		}
	}
}
