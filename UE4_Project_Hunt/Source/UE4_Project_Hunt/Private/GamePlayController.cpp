// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GamePlayStatics.h"
#include "DrawDebugHelpers.h"
#include "GamePlayController.h"

AGamePlayController::AGamePlayController()
{
	LineTraceRange = 2000;
	CrosshairXLocation = 0.5f;
	CrosshairXLocation = 0.333f;
}

void AGamePlayController::BeginPlay()
{
	Super::BeginPlay();

	/**Set the current state to playing*/
	SetCurrentState(EGamePlayState::EPlying);


	/**Test if the player controller is posseisng the player*/
	auto PlayerController = GetPlayerController();

	if (!PlayerController)
	{
		UE_LOG(LogTemp, Error, TEXT("Controller not posseisng a player Character"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Controller is posseisng : %s"), *PlayerController->GetName())
	}
}

void AGamePlayController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	/*see if the player health is near 0*/
	if (GetPlayerController())
	{
		if (FMath::IsNearlyZero(GetPlayerController()->GetHealth(), 0.001f))
		{
			SetCurrentState(EGamePlayState::EGameOver);
		}
	}
	AimTowrdsCrosshir();
}

void AGamePlayController::AimTowrdsCrosshir()
{
	if (!GetPlayerController()) {return;}

	FVector HitLocation;
	
	if (GetSightRayHitLocation(HitLocation))
	{
		// tell the controller player hitting this point
		UE_LOG(LogTemp, Warning, TEXT("HitLocation: %s"), *(HitLocation.ToString()))
	}
}

/**Get World Location of the line-trace through cross hair, true if hits the landscape*/
bool AGamePlayController::GetSightRayHitLocation(FVector& HitLocation) const
{
	/* Find the cross hair position*/
	int32 ViewprotSizeX, ViewprotSizeY;
	GetViewportSize(ViewprotSizeX, ViewprotSizeY);
	auto ScreenLocation = FVector2D(ViewprotSizeX * CrosshairXLocation, ViewprotSizeY * CrosshairXLocation);

	/* "De-project" the screen position of the cross hair to world direction*/
	FVector LookDirection;
	if (GetLookDirection(ScreenLocation, LookDirection))
	{
		/* line-trace along that look direction, and see what we hit (Up to the max range)*/
		GetLookVectorHitLocation(LookDirection, HitLocation);
	}
	return true;
}

bool  AGamePlayController::GetLookVectorHitLocation(FVector LookDirection, FVector& HitLocation) const
{
	FHitResult HitResult;
	auto StartLocation = PlayerCameraManager->GetCameraLocation();
	auto EndLocation = StartLocation + (LookDirection * LineTraceRange);

	if (GetWorld()->LineTraceSingleByChannel(HitResult, StartLocation, EndLocation,
		ECollisionChannel::ECC_Visibility))
	{
		HitLocation = HitResult.Location;
		return true;
	}
	HitLocation = FVector(0);
	return false; // Line-Trace didn't succeed
}

bool AGamePlayController::GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const
{
	FVector CameraLocation; // to be discarded
	return DeprojectScreenPositionToWorld(ScreenLocation.X, 
	ScreenLocation.Y, 
	CameraLocation, 
	LookDirection
	);
}

APlayerCharacter* AGamePlayController::GetPlayerController()
{
	return Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
}

/** Setup the player state to see if the player dead or no*/
EGamePlayState AGamePlayController::GetCurrentState() const
{
	return CurrentState;
}

void AGamePlayController::SetCurrentState(EGamePlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(CurrentState);
}

/*
* if the player health is 0 the Game restart
* TODO if the player health is 0 open HUD screen
*/
void AGamePlayController::HandleNewState(EGamePlayState NewState)
{
	switch (NewState)
	{
	case EGamePlayState::EPlying:
	{
		// do nothing
	}
	break;

	case EGamePlayState::EGameOver:
	{
		UGameplayStatics::OpenLevel(this, FName(*GetWorld()->GetName()), false);
	}

	case EGamePlayState::EUnknown:
	{
		// do nothing
	}
	}
}