// Fill out your copyright notice in the Description page of Project Settings.


#include "StopMovingNotifyState.h"
#include "PlayerCharacter.h"

UStopMovingNotifyState::UStopMovingNotifyState()
{

}

void UStopMovingNotifyState::NotifyTick(USkeletalMeshComponent* MeshComp, UAnimSequenceBase* Animation, float FrameDeltaTime)
{
	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			if (Player->GetCurrntAttack() == EAttackType::MELEE_SPECIAL)
			{
				Player->SetIsKeyboardEnabled(false);
			}
		}
	}
}
