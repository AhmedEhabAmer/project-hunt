// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "HealActor.h"
#include "HuntAICharacter.generated.h"

UCLASS()
class UE4_PROJECT_HUNT_API AHuntAICharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	AHuntAICharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	UPROPERTY(EditAnywhere, Category = AI)
	class UBehaviorTree* BehaviorTree;

	UPROPERTY(VisibleAnywhere, Category = AI)
	class UPawnSensingComponent* PawnSensingComp;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn", meta = (AllowPrivateAcsess = "true"))
	TSubclassOf<AHealActor> ActorToSpawn;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Spawn", meta = (AllowPrivateAcsess = "true"))
	int32 NumberOfDrops;

	void DeadUpDate(float& CurrntHealth);
	void HealSpawn(FVector& DeadLocation, FRotator SpwanRotation);

	/*
	* Setup the health value and make sure it is right all the time
	* Setup the damage Timer and the damage state if the player take any damage
	* it appeared in the screen by the heath counter
	*/
	struct FTimerHandle MemberTimerHandle;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float FullHealth;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float Health;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Health")
	float HealthPrecentage;

	UFUNCTION(BlueprintPure, Category = "Health")
	float GetHealth();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void UpdateHealth(float HealthChange);

	UFUNCTION()
	void SetDamageState();

	UFUNCTION()
	void DamageTimer();

	UFUNCTION()
	float TakeDamage(float DamageAmount, struct FDamageEvent const& DamageEvent,
	class AController* EventInstigator, AActor* DamageCauser);

	FTimerHandle DamageTimerHandle;

private:
	
	UFUNCTION()
	void OnPlayerCaught(APawn* InPawn);
};
