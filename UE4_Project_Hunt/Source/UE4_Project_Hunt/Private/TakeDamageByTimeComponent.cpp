// Fill out your copyright notice in the Description page of Project Settings.


#include "TakeDamageByTimeComponent.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"

// Sets default values for this component's properties
UTakeDamageByTimeComponent::UTakeDamageByTimeComponent()
{
	// Set this component to be initialized when the game starts, and to be ticked every frame.  You can turn these features
	// off to improve performance if you don't need them.
	PrimaryComponentTick.bCanEverTick = true;

	// ...
}


// Called when the game starts
void UTakeDamageByTimeComponent::BeginPlay()
{
	Super::BeginPlay();	
}


// Called every frame
void UTakeDamageByTimeComponent::TickComponent(float DeltaTime, ELevelTick TickType, FActorComponentTickFunction* ThisTickFunction)
{
	Super::TickComponent(DeltaTime, TickType, ThisTickFunction);
	
	
}

/*void UTakeDamageByTimeComponent::ApplyDamage()
{
	
}*/