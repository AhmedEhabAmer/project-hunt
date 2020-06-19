// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "BehaviorTree/BTTaskNode.h"
#include "BTSelectPatrolPoint.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_HUNT_API UBTSelectPatrolPoint : public UBTTaskNode
{
	GENERATED_BODY()
	
public:
	
	/*this function will execute a task that will define it self*/
	virtual EBTNodeResult::Type ExecuteTask(UBehaviorTreeComponent& OwnerComp, uint8* NodeMemory) override;


};
