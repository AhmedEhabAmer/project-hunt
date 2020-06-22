// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UStaticMeshComponent;
class USpringArmComponent;
class UCameraComponent;

UCLASS()
class UE4_PROJECT_HUNT_API APlayerCharacter : public ACharacter
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	/*Setup player movement and sprint*/
	void MoveForward(float Value);
	void MoveRight(float Value);
	void SprintStart();
	void SprintEnd();

	/*Setup player camera and mesh
	* Setup the base for the controller
	*/

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Sittings")
	UStaticMeshComponent* PlayerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Sittings")
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Sittings")
	UCameraComponent* PlayerCamera;

	/*Setup the base for the controller*/
	void LookUpRate(float Value);
	void TrunRate(float Value);

	UPROPERTY(EditDefaultsOnly, Category = "Controller")
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, Category = "Controller")
	float BaseTurnRate;

	/*Setup the mouse sensitivity*/
	void LookUp(float AxisValue);
	void Turn(float AxisValue);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sensitivity")
	float Mousesensitivity;

	/*Setup character speed*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Character Movment : Walking")
	float SprintSpeedMultiplier;

public:
	/*
	* Setup the health value and make sure it is right all the time
	* TODO If the player take any damage the screen will flash
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

	UFUNCTION(BlueprintPure, Category = "Health")
	FText GetHealthInText();

	UFUNCTION(BlueprintPure, Category = "Health")
	bool bPlayerFlash();

	UFUNCTION(BlueprintCallable, Category = "Health")
	void UpdateHealth(float HealthChange);

	UFUNCTION()
	void DamageTimer();

	UFUNCTION()
	void SetDamageState();

	UFUNCTION()
	float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent,
	class AController * EventInstigator, AActor * DamageCauser);

	/*Setup the mouse Relative*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Relative")
	FVector CameraRelativeLoacation = FVector(0.f, 30.f, 70.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Relative")
	FRotator CameraRelativeRotation = FRotator(0.f, 30.f, 70.f);

private:
	/*
	* this is for the damage function
	* The timer handle for make the time running well
	* the timer per sec and damage you can edit it from the BP not need to open the code for it
	*/
	UPROPERTY(EditAnywhere, Category = "Damage")
	float TimerPerSeconds = 1.f;

	UPROPERTY(EditAnywhere, Category = "Damage")
	float  TimerDamage = 1.f;

	void TimeToTakeDamage();

	void StartTimer();

	FTimerHandle DamageTimerHandle;
};
