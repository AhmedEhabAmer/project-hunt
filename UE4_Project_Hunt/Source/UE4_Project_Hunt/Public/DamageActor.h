// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "DamageActor.generated.h"

class UBoxComponent;

UCLASS()
class UE4_PROJECT_HUNT_API ADamageActor : public AActor
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	ADamageActor();

public:

	UPROPERTY(EditAnywhere)
		UParticleSystemComponent* Particle;

	UPROPERTY(EditAnywhere)
		UBoxComponent* MyBoxComponent;

	UPROPERTY(EditAnywhere)
		TSubclassOf<UDamageType> FireDamageType;

	UPROPERTY(EditAnywhere)
		AActor* MyCharacter;

	UPROPERTY(EditAnywhere)
		FHitResult MyHit;

	UPROPERTY(EditAnywhere)
		FVector BoxSize = FVector(50.f, 50.f, 50.f);

	UPROPERTY(EditAnywhere, Category = "Damage")
		float DamageAmont = 20.f;

	UPROPERTY(EditAnywhere, Category = "Damage")
		float TimeToTakeDamageInSeconds = 1.f;

	bool bCanApplyDamage;
	FTimerHandle DamageTimerHandle;

	// declare component overlap begin function
	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
					class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
					const FHitResult& SweepResult);

	// declare component overlap end function
	UFUNCTION()
		void OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
						  class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	UFUNCTION()
		void ApplyDamage();
};