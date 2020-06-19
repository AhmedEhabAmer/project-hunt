// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "HuntAIController.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_HUNT_API AHuntAIController : public AAIController
{
	GENERATED_BODY()
	
public:

	/*Our Behavior tree component*/
	class UBehaviorTreeComponent* BehaviorTreeComp;

	/*Our blackboard component*/
	UBlackboardComponent* BlackBoardComp;

	/*Backboard keys*/
	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName LocationToGo;

	UPROPERTY(EditDefaultsOnly, Category = AI)
	FName PlayerKey;

	/*
	*this array to store all the patrol points 
	*and let us use it instead of using Actors around the level
	*by taking all the actors array and store it the target point
	*and find the next target to walk to
	*/
	TArray<AActor*> PatrolPoint;

	/*This function calls when we start posses a pawn*/
	virtual void OnPossess(APawn* InPawn) override;

	int32 CurrentPatrolPoint;

public:

	AHuntAIController();

	/*When Ai catch the player this function will called*/
	void SetPlayerCaught(APawn* InPawn);

	/*Inline getter functions*/
	FORCEINLINE UBlackboardComponent* GetBalckBoardComp() const { return BlackBoardComp; }
	FORCEINLINE TArray<AActor*> GetPatrolPont() const { return PatrolPoint; }
};
