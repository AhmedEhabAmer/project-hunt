// Fill out your copyright notice in the Description page of Project Settings.


#include "WindMillRotation.h"
#include "Components/StaticMeshComponent.h"
#include "Components/TimelineComponent.h"

// Sets default values
AWindMillRotation::AWindMillRotation()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	WindMill = CreateDefaultSubobject<UStaticMeshComponent>("WindMill");

	RollValue = 5.f;
	RotateTimePerSec = 5;
}

// Called when the game starts or when spawned
void AWindMillRotation::BeginPlay()
{
	Super::BeginPlay();
	
	GetWorldTimerManager().SetTimer(TimerHandle, this, &AWindMillRotation::RotateTime, RotateTimePerSec, true);
}

void AWindMillRotation::RotateTime()
{
	FQuat QuatRotation = FRotator(RollValue, 0.f, 0.f).Quaternion();
	AddActorLocalRotation(QuatRotation, false, 0, ETeleportType::None);
}

// Called every frame
void AWindMillRotation::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}


