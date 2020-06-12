// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "PlayerCharacter.h"
#include "HealActor.generated.h"

class UStaticMeshComponent;

UCLASS()
class UE4_PROJECT_HUNT_API AHealActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AHealActor();

public:
	
	UPROPERTY(EditAnywhere, Category = "Static Mesh")
	UStaticMeshComponent* HealingMesh;


	UFUNCTION()
	void OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor);

	UPROPERTY(EditAnywhere)
	APlayerCharacter* MyCharacter;

	UPROPERTY(EditAnywhere)
	int32 HealthAmmont;

};
