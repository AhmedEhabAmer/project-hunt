// Fill out your copyright notice in the Description page of Project Settings.


#include "BTSelectPatrolPoint.h"
#include "AITargetPoint.h"
#include "HuntAIController.h"
#include "Behaviortree/BlackboardComponent.h"


EBTNodeResult::Type UBTSelectPatrolPoint::ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory)
{
	AHuntAIController* AICon = Cast<AHuntAIController>(OwnerComp.GetAIOwner());

	if (AICon)
	{
		/*Get BlackBoard Component*/
		UBlackboardComponent* BlackBoardComp = AICon->GetBalckBoardComp();

		AAITargetPoint* CurrentPoint = Cast<AAITargetPoint>(BlackBoardComp->GetValueAsObject("LocationToGo"));

		TArray<AActor*> AvailablePatrolPoints = AICon->GetPatrolPont();

		AAITargetPoint* NextPatrolPoint = nullptr;

		if (AICon->CurrentPatrolPoint != AvailablePatrolPoints.Num() - 1)
		{
			NextPatrolPoint = Cast<AAITargetPoint>(AvailablePatrolPoints[++AICon->CurrentPatrolPoint]);			
		}
		else // if there is not any more points to go to
		{
			NextPatrolPoint = Cast<AAITargetPoint>(AvailablePatrolPoints[0]);
			AICon->CurrentPatrolPoint = 0;
		}

		BlackBoardComp->SetValueAsObject("LocationToGo", NextPatrolPoint);

		return EBTNodeResult::Succeeded;
	}
	return EBTNodeResult::Failed;
}
