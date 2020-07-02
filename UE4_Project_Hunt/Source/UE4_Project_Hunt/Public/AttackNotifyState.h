// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "AttackNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_HUNT_API UAttackNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
		UAttackNotifyState();

public:

   virtual void NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration) override;

   virtual void NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation) override;
};
