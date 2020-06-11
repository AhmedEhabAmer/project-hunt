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

	void MoveForward(float Value);
	void MoveRight(float Value);

	// Setup player camera and mesh

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Player Sittings")
	UStaticMeshComponent* PlayerMesh;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Sittings")
	USpringArmComponent* CameraSpringArm;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Sittings")
	UCameraComponent* PlayerCamera;

public:
	/*
	* Setup the health value and make sure it is right all the time
	* If the player take any damage the screen will flash 
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
	float RecivePointDamage(float Damage, const class UDamageType * DamageType, FVector HitLocation,
	FVector HitNormal, class UPrimitiveComponent * HitComponent, FName BoneName, FVector ShotFromDirection, 
	class AController * InstigatedBy, AActor * DamageCauser, const FHitResult & HitInfo);
};

