// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "AIController.h"
#include "PlayerCharacter.h"
#include "HuntAIController.generated.h"
class UBehaviorTreeComponent;


/**
 * 
 */
UCLASS()
class UE4_PROJECT_HUNT_API AHuntAIController : public AAIController
{
	GENERATED_BODY()
	
public:
	/*Our Behavior tree*/
	UBehaviorTreeComponent* BehavirorTree;

	/*Our blackboard component*/
	UBlackboardComponent* BlackBoardComp;

	/*BlackBoard Keys*/
	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName LocationToGoKeys;

	UPROPERTY(EditDefaultsOnly, Category = "AI")
	FName PlayerKeys;

	TArray<AActor*> PatrolPoints;

	virtual void OnPossess(APawn* InPawn) override;

public:
	
	AHuntAIController();

	/*Inline gritter functions*/
	FORCEINLINE UBlackboardComponent* GetBlackBoardComp() const {return BlackBoardComp;}
	FORCEINLINE TArray<AActor*> GetPatrolPoints() const {return PatrolPoints;}
};
