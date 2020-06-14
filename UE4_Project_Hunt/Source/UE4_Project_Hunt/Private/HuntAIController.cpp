// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntAIController.h"

AHuntAIController::AHuntAIController()
{

}

void AHuntAIController::BeginPlay()
{
	Super::BeginPlay();

	auto AIController = GetController();
	auto AIFoundPlayer = GetPlayer();
	if (!AIFoundPlayer)
	{
		UE_LOG(LogTemp, Error, TEXT("AiController not possisng a tank"))
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("AiController is possisng %s"), *(GetPlayer()->GetName()))
	}
}

APlayerCharacter* AHuntAIController::GetPlayer() const 
{
	auto PlayerPawn = GetWorld()->GetFirstPlayerController()->GetPawn();
	if (!PlayerPawn) {return nullptr;}
	return Cast<APlayerCharacter>(PlayerPawn);
}

APlayerCharacter * AHuntAIController::GetController() const
{
	return Cast<APlayerCharacter>(GetPawn());
}
