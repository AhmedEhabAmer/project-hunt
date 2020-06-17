// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntAICharacter.h"
#include "HuntAIController.h"
#include "BeHaviorTree/BehaviorTree.h"
#include "perception/PawnSensingComponent.h"

// Sets default values
AHuntAICharacter::AHuntAICharacter()
{
	/*Initialize senses*/
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
	PawnSensingComp->SetPeripheralVisionAngle(90.f);
}

// Called when the game starts or when spawned
void AHuntAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AHuntAICharacter::OnPlayerCaught);
	}

}

void AHuntAICharacter::OnPlayerCaught(APawn* InPawn)
{

	/*Get a reference to the player controller*/
	AHuntAIController* AIController = Cast<AHuntAIController>(GetController());

	if (AIController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You have been caught"));
		AIController->SetPlayerCaught(InPawn);
	}
}

// Called to bind functionality to input
void AHuntAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
