// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/DataTable.h"
#include "GameFramework/Character.h"
#include "PlayerCharacter.generated.h"

class UStaticMeshComponent;
class USceneComponent;
class USpringArmComponent;
class UCameraComponent;
class UMaterialInstanceDynamic;
class UAnimMontage;
class UBoxComponent;
class UDataTable;

USTRUCT(BlueprintType)
struct FPlayerAttackMontage : public FTableRowBase
{	
	GENERATED_BODY()
	
	/**Initialize animation montage calling*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	UAnimMontage* MeleeLightAttackAinmation;
	
	/**Amount of sections within our montage*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	int32 AnimSectionCount;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
	FString Description;
};

USTRUCT(BlueprintType)
struct FMeleeCollisionProfile
{
	GENERATED_BODY()

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Enabled; 

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
	FName Desabled;
	
	// default contractor
	FMeleeCollisionProfile()
	{
		Enabled = FName(TEXT("Weapon"));
		Desabled = FName(TEXT("NoCollisoin"));
	}

};

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

	/**Initialize Attack event*/
	void AttackStart();
	void AttackEnd();
	
	/**Triggers attack animation based on user input*/
	void AttackInput();

	/**
	* Triggered when the collision hit event fires between our weapon and enemy entities
	*/
	UFUNCTION()
	void OnHitAttack(UPrimitiveComponent* HitComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp,
	FVector NormalImpulse, const FHitResult& Hit);

	/**Initialize camera spring arm*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Sittings")
	USpringArmComponent* CameraSpringArm;

	/**Initialize player camera*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Sittings")
	UCameraComponent* PlayerCamera;

	/**Initialize animation montage calling*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAcsess = "true"))
	UAnimMontage* MeleeLightAttackAinmation;

	/**Light Melee attack data table*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Animation", meta = (AllowPrivateAcsess = "true"))
	UDataTable* LightAttackDataTable;

	/**Initialize animation variable*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation", meta = (AllowPraivateAcsess = "true"))
	float AnimationVariable;

	/**Initialize sword mesh*/
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes", meta = (AllowPrivateAcsess = "true"))
	UStaticMeshComponent* PlayerSwordMesh;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Meshes", meta = (AllowPraivateAcsess = "true"))
	USceneComponent* PlayerSword;

	/**Initialize Attack Collision*/
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Collison", meta = (AllowPrivateAcsess = "true"))
	UBoxComponent* SwordCollision;


protected:

	/**
	* Functions for player movement and sprint
	* Functions for controller movement 
	* Functions for mouse sensitivity
	*/
	void MoveForward(float Value);
	void MoveRight(float Value);
	void LookUp(float AxisValue);
	void Turn(float AxisValue);
	void LookUpRate(float Value);
	void TrunRate(float Value);
	void SprintStart();
	void SprintEnd();

	/**Pause Game Event*/
	void PauseGame(bool bIsPaused);
	void Pause();

	FName SocketName;
	
	UPROPERTY(EditDefaultsOnly, Category = "Controller")
	float BaseLookUpRate;

	UPROPERTY(EditDefaultsOnly, Category = "Controller")
	float BaseTurnRate;

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "sensitivity")
	float Mousesensitivity;

	/**Setup character speed*/
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
	void MatUpdate(float& BlendUpdate);

	UFUNCTION()
	float TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent,
	class AController * EventInstigator, AActor * DamageCauser);

	/*Setup the mouse Relative*/
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Relative")
	FVector CameraRelativeLoacation = FVector(0.f, 30.f, 70.f);

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Camera Relative")
	FRotator CameraRelativeRotation = FRotator(0.f, 30.f, 70.f);

	/**
	* Initialize Light Attack damage
	*/
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Attack : Light", meta = (AllowPrivateAcsess = "true"))
	float LightAttackDamage;

	FHitResult AIHit;
private:
	
	UAnimInstance* AnimInstance;

	/**Reference to attack data table*/
	FPlayerAttackMontage* LightAttackMontage;

	/**Call the contractor definition*/
	FMeleeCollisionProfile MeleeAttackCollisionProfile;

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

	/**
	* This dynamic material have a reference to player health
	* If the player take any damage the material will change
	* This dynamic material has a bind with material blueprint
	* Array is the manger for the bind change
	* Every time the player got any damage the array number will increase with the damage amount
	* When the array number increase the bland will change the number from 0 - 100
	* When the bind change with array the blueprint blend will change with the array
	* If the blueprint blend change the color transaction start
	*/
	UMaterialInstanceDynamic* MaterialChange;
};
