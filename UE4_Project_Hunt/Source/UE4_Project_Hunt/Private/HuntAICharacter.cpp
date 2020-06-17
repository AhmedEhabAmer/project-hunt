// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntAICharacter.h"

// Sets default values
AHuntAICharacter::AHuntAICharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AHuntAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AHuntAICharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void AHuntAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

