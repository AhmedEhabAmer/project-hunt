// Fill out your copyright notice in the Description page of Project Settings.


#include "HealActor.h"

// Sets default values
AHealActor::AHealActor()
{
 	OnActorBeginOverlap.AddDynamic(this, &AHealActor::OnOverlap);
}

void AHealActor::OnOverlap(AActor* MyOverlappedActor, AActor* OtherActor)
{
	if ( (OtherActor != nullptr) && (OtherActor != this) )
	{
		MyCharacter = Cast<APlayerCharacter>(OtherActor);

		if (MyCharacter && MyCharacter->GetHealth() < 1.0f)
		{
			MyCharacter->UpdateHealth(HealthAmmont);
			Destroy();
		}
	}
}
