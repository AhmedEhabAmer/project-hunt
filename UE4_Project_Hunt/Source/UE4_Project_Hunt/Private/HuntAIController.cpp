// Fill out your copyright notice in the Description page of Project Settings.

#include "HuntAIController.h"
#include "..\Public\HuntAIController.h"
#include "HuntAICharacter.h"
#include "AITargetPoint.h"
#include "BeHaviorTree/BehaviorTreeComponent.h"
#include "BeHaviorTree/BlackboardComponent.h"
#include "BeHaviorTree/BehaviorTree.h"
#include "Kismet/GameplayStatics.h"

AHuntAIController::AHuntAIController()
{
	/*Initialize BlackBoard and BehaviorTree*/
	BehaviorTreeComp = CreateDefaultSubobject<UBehaviorTreeComponent>("BehaviorTreeComp");
	BlackBoardComp = CreateDefaultSubobject<UBlackboardComponent>("BlackBoardComp");

	/*Initialize blackboard keys*/
	PlayerKey = "Target";
	LocationToGo = "LocationToGo";

	CurrentPatrolPoint = 0;
}

void AHuntAIController::OnPossess(APawn* InPawn)
{

	/*Get Reference to the character*/
	AHuntAICharacter* AICharacter = Cast<AHuntAICharacter>(InPawn);

	if (AICharacter)
	{
		if (AICharacter->BehaviorTree->BlackboardAsset)
		{
			BlackBoardComp->InitializeBlackboard(*(AICharacter->BehaviorTree->BlackboardAsset));
		}

		/*Populate patrol point array*/
		UGameplayStatics::GetAllActorsOfClass(GetWorld(), AAITargetPoint::StaticClass(), PatrolPoint);

		BehaviorTreeComp->StartTree(*AICharacter->BehaviorTree);
	}
}

void AHuntAIController::SetPlayerCaught(APawn* InPawn)
{
	if (BlackBoardComp)
	{
		BlackBoardComp->SetValueAsObject(PlayerKey, InPawn);
	}
}
