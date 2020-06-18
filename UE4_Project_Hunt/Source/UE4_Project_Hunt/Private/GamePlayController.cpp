// Fill out your copyright notice in the Description page of Project Settings.

#include "GamePlayController.h"
#include "Kismet/GamePlayStatics.h"
#include "DrawDebugHelpers.h"

AGamePlayController::AGamePlayController()
{
}

void AGamePlayController::BeginPlay()
{
	Super::BeginPlay();

	/**Set the current state to playing*/
	SetCurrentState(EGamePlayState::EPlying);

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