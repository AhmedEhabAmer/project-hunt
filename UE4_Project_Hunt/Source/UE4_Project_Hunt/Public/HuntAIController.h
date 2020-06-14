// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlayerCharacter.h"
#include "HuntAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_HUNT_API AHuntAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	
	AHuntAIController();

	virtual void BeginPlay() override;

public:

	APlayerCharacter* GetController() const;

	APlayerCharacter* GetPlayer() const;
};
