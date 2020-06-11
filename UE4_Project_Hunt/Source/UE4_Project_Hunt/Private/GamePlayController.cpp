// Fill out your copyright notice in the Description page of Project Settings.

#include "Kismet/GamePlayStatics.h"
#include "GamePlayController.h"

AGamePlayController::AGamePlayController()
{
	
}

void AGamePlayController::BeginPlay()
{
	Super::BeginPlay();

	SetCurrentState(EGamePlayState::EPlying);

	MyCharacther = Cast<APlayerCharacter>(UGameplayStatics::GetPlayerPawn(this, 0));
}

void AGamePlayController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (MyCharacther)
	{
		if (FMath::IsNearlyZero(MyCharacther->GetHealth(), 0.001f))
		{
			SetCurrentState(EGamePlayState::EGameOver);
		}
	}
}


EGamePlayState AGamePlayController::GetCurrentState() const
{
	return CurrentState;
}

void AGamePlayController::SetCurrentState(EGamePlayState NewState)
{
	CurrentState = NewState;
	HandleNewState(CurrentState);
}

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