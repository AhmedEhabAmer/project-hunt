// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntAIController.h"
#include "HuntAICharacter.h"
#include "AITargetPoint.h"
#include "BeHaviorTree/BehaviorTree.h"
#include "BeHaviorTree/BlackBoardComponent.h"
#include "BeHaviorTree/BehaviorTreeComponent.h"

AHuntAIController::AHuntAIController()
{

}

void AHuntAIController::OnPossess(APawn* InPawn)
{
	Super::Possess(InPawn);

}


