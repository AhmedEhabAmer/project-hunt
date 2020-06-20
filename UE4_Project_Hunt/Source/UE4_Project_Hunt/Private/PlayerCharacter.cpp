// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Components/TimelineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false; // Tick function is off

	/*
	* Initialize the the spring arm and the camera
	* attach it to the root (player capsule)
	*/
	CameraSpringArm = CreateDefaultSubobject<USpringArmComponent>("Camera SpringArm");
	CameraSpringArm->SetupAttachment(RootComponent);
	CameraSpringArm->bUsePawnControlRotation = true;

	PlayerCamera = CreateDefaultSubobject<UCameraComponent>("Player Camera");
	PlayerCamera->SetupAttachment(CameraSpringArm);
	PlayerCamera->SetRelativeLocation(CameraRelativeLoacation);
	PlayerCamera->SetRelativeRotation(CameraRelativeRotation);


	/*Setup the base for the controller BP can edit*/
	BaseTurnRate = 0.45;
	BaseLookUpRate = 0.45;

	Mousesensitivity = 1.f;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	/**Setup the Heath to be ready if damage event starts*/
	FullHealth = 100.f;
	Health = FullHealth;
	HealthPrecentage = 1.f;
	bCanBeDamaged = true;

	/*Start the give damage every X second timer*/
	StartTimer();
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

 /*Call the timer to start take damage*/
void APlayerCharacter::StartTimer()
{
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this,
		&APlayerCharacter::TimeToTakeDamage, TimerPerSeconds, true);
}

/*The player take damage every X second BP can edit that*/
void APlayerCharacter::TimeToTakeDamage()
{	
	UpdateHealth(-TimerDamage);
	StartTimer();
}

float APlayerCharacter::GetHealth()
{
	return HealthPrecentage;
}

/*Setup the Text for the health to make it count or bar*/
FText APlayerCharacter::GetHealthInText()
{
	int32 HP = FMath::RoundHalfFromZero(HealthPrecentage * 100);
	FString HPS = FString::FromInt(HP);
	FString HealthHUD = HPS + FString(TEXT("%"));
	FText HPText = FText::FromString(HealthHUD);
	return HPText;
}

void APlayerCharacter::SetDamageState()
{
	bCanBeDamaged = true;
}

bool APlayerCharacter::bPlayerFlash()
{
	return false;
}

/*To start take damage if the player overlap any damage actor*/
void APlayerCharacter::DamageTimer()
{
	GetWorldTimerManager().SetTimer(MemberTimerHandle, this,
		&APlayerCharacter::SetDamageState, 2.0f, false);
}

/*The take damage function if the player overlap any damage actor or enemy hit this function will apply damage*/
float APlayerCharacter::TakeDamage(float DamageAmount, struct FDamageEvent const & DamageEvent,
	class AController * EventInstigator, AActor * DamageCauser)
{
	bCanBeDamaged = false;
	UpdateHealth(-DamageAmount);
	DamageTimer();
	TimeToTakeDamage();
	return DamageAmount;
}

/*Update the health bar*/
void APlayerCharacter::UpdateHealth(float HealthChange)
{
	Health += HealthChange;
	Health = FMath::Clamp(Health, 0.0f, FullHealth);
	HealthPrecentage = Health / FullHealth;

}

/*setup the movement*/
void APlayerCharacter::MoveForward(float Value)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0., Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::X);
	AddMovementInput(Direction, Value);
}

void APlayerCharacter::MoveRight(float Value)
{
	const FRotator Rotation = Controller->GetControlRotation();
	const FRotator YawRotation(0., Rotation.Yaw, 0);

	const FVector Direction = FRotationMatrix(YawRotation).GetUnitAxis(EAxis::Y);
	AddMovementInput(Direction, Value);
}

/*
* this 2 functions is only for the controller
* you cant multiple the rate to the delta for the mouse cuz the mouse already have delta on it
*/
void APlayerCharacter::TrunRate(float Value)
{
	AddControllerYawInput(Value * BaseTurnRate * GetWorld()->GetDeltaSeconds());
}

void APlayerCharacter::LookUpRate(float Value)
{
	AddControllerPitchInput(Value * BaseLookUpRate * GetWorld()->GetDeltaSeconds());
}

/**Setup mouse movement and Sensitivity*/
void APlayerCharacter::LookUp(float AxisValue)
{
	float MouseSen = FMath::Clamp(Mousesensitivity, 0.f, 1.f); // Max sensitivity it (1)

	AddControllerPitchInput(AxisValue * MouseSen);
}

void APlayerCharacter::Turn(float AxisValue)
{
	float MouseSen = FMath::Clamp(Mousesensitivity, 0.f, 1.f); // Max sensitivity it (1)

	AddControllerYawInput(AxisValue * MouseSen);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/**Setup the jump for the controller and the keyboard*/
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	/**Setup all the Axis for the controller and the keyboard*/
	PlayerInputComponent->BindAxis("Move Forward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right", this, &APlayerCharacter::MoveRight);
	
	/**Setup the camera movement for mouse*/
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	/**Setup the camera movement for controller*/
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TrunRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpRate);
}