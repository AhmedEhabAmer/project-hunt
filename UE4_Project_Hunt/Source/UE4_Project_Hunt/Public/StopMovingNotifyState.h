// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimNotifies/AnimNotifyState.h"
#include "StopMovingNotifyState.generated.h"

/**
 * 
 */
UCLASS()
class UE4_PROJECT_HUNT_API UStopMovingNotifyState : public UAnimNotifyState
{
	GENERATED_BODY()
	
public:
	
	UStopMovingNotifyState();

	virtual void NotifyTick(class USkeletalMeshComponent* MeshComp, class UAnimSequenceBase* Animation, float FrameDeltaTime) override;
};
