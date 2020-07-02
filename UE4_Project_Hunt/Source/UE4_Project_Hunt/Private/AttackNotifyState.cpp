// Fill out your copyright notice in the Description page of Project Settings.


#include "AttackNotifyState.h"
#include "PlayerCharacter.h"
#include "Engine.h"

UAttackNotifyState::UAttackNotifyState()
{

}

void UAttackNotifyState::NotifyBegin(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation, float TotalDuration)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, __FUNCTION__);
	}

	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->AttackStart();
		}

	}
}

void UAttackNotifyState::NotifyEnd(USkeletalMeshComponent * MeshComp, UAnimSequenceBase * Animation)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Cyan, __FUNCTION__);
	}

	if (MeshComp != NULL && MeshComp->GetOwner() != NULL)
	{
		APlayerCharacter* Player = Cast<APlayerCharacter>(MeshComp->GetOwner());
		if (Player != NULL)
		{
			Player->AttackEnd();
		}

	}
}