// Fill out your copyright notice in the Description page of Project Settings.

#include "PlayerCharacter.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"
#include "Components/TimelineComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Camera/CameraComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Kismet/GameplayStatics.h"
#include "GameFramework/Character.h"
#include "GameFramework/CharacterMovementComponent.h"
#include "Materials/MaterialInstanceDynamic.h"
#include "Materials/MaterialInterface.h"
#include "GamePlayController.h"

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

	/**Initialize Sword socket*/
	PlayerSword = CreateDefaultSubobject<USceneComponent>("Sword Scene");

	/**Initialize Sword mesh*/
	PlayerSwordMesh = CreateDefaultSubobject<UStaticMeshComponent>("Player sword");
	PlayerSwordMesh->SetupAttachment(PlayerSword);

	/**Initialize Sword collision*/
	SwordCollision = CreateDefaultSubobject<UBoxComponent>("Sword Collision");
	SwordCollision->SetupAttachment(PlayerSwordMesh);
	SwordCollision->SetCollisionProfileName("NoCollision");
	SwordCollision->SetNotifyRigidBodyCollision(false);
	SwordCollision->SetHiddenInGame(false); // Show the collision while game is running
	
	/**Initialize the base for the controller BP can edit*/
	BaseTurnRate = 0.45;
	BaseLookUpRate = 0.45;

	/**sensitivity for mouse BP can edit*/
	Mousesensitivity = 1.f;

	/**Initialize the sprint speed*/
	SprintSpeedMultiplier = 1.f;

	/**Load animation montage*/
	static ConstructorHelpers::FObjectFinder<UAnimMontage> MeleeLightAttackAinmationObject((TEXT("AnimMontage'/Game/Animations/Actions/Attack/Montage/M_LightAttack_1.M_LightAttack_1'")));
	if (MeleeLightAttackAinmationObject.Succeeded())
	{
		MeleeLightAttackAinmation = MeleeLightAttackAinmationObject.Object;
	}
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

	/**Setup material change*/
	auto Char = FindComponentByClass<USkeletalMeshComponent>();
	auto ChangeMaterial = Char->GetMaterial(1);

	MaterialChange = UMaterialInstanceDynamic::Create(ChangeMaterial, NULL);
	Char->SetMaterial(1, MaterialChange);

	/**Attach collision components to sockets based on transform defenestrations*/
	const FAttachmentTransformRules AttachRules(EAttachmentRule::SnapToTarget, EAttachmentRule::SnapToTarget,
	EAttachmentRule::KeepWorld, false);

	PlayerSword->AttachToComponent(GetMesh(), AttachRules, "SwordAttackPosition");

	/**Initialize overlap event*/
	SwordCollision->OnComponentHit.AddDynamic(this, &APlayerCharacter::OnHitAttack);
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
	return DamageAmount;
}

/*Update the health bar*/
void APlayerCharacter::UpdateHealth(float HealthChange)
{
	/**Update health*/
	Health += HealthChange;
	Health = FMath::Clamp(Health, 0.0f, FullHealth);
	HealthPrecentage = Health / FullHealth;

	MatUpdate(HealthPrecentage);
}

/**Update Character Material*/
void APlayerCharacter::MatUpdate(float& BlendUpdate)
{
	/**Array that Set the value of the blend Material*/
	TArray<float> BlendValue;
	BlendValue.SetNum(100);

	for (int32 Index = 0; Index != BlendValue.Num(); ++Index)
	{
		float blend = BlendUpdate;
		MaterialChange->SetScalarParameterValue(TEXT("Blend"), blend);
	}
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

/*Setup sprint*/
void APlayerCharacter::SprintStart()
{
	GetCharacterMovement()->MaxWalkSpeed *= SprintSpeedMultiplier;
}

void APlayerCharacter::SprintEnd()
{
	GetCharacterMovement()->MaxWalkSpeed /= SprintSpeedMultiplier;
}

/*
* this 2 functions is only for the controller
* you cant multiple the rate to the delta for the mouse because the mouse already have delta on it
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
	float MouseSen = FMath::Clamp(Mousesensitivity, 0.f, 1.f); // Max sensitivity is (1)

	AddControllerPitchInput(AxisValue * MouseSen);
}

void APlayerCharacter::Turn(float AxisValue)
{
	float MouseSen = FMath::Clamp(Mousesensitivity, 0.f, 1.f); // Max sensitivity is (1)

	AddControllerYawInput(AxisValue * MouseSen);
}

/**If player hit pause key the game will pause (default = false)*/
void  APlayerCharacter::PauseGame(bool bIsPaused)
{
	AGamePlayController* const MyChar = Cast<AGamePlayController>(GEngine->GetFirstLocalPlayerController(GetWorld()));

	if (MyChar != NULL)
	{
		MyChar->SetPause(bIsPaused);
	}
}

/**Call the boll and set it to true*/
void APlayerCharacter::Pause()
{
	PauseGame(true);
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

	/**Setup the jump for the controller and the keyboard*/
	PlayerInputComponent->BindAction("Jump", IE_Pressed, this, &ACharacter::Jump);
	PlayerInputComponent->BindAction("Jump", IE_Released, this, &ACharacter::StopJumping);

	/**Setup sprint keys*/
	PlayerInputComponent->BindAction("Sprint", IE_Pressed, this, &APlayerCharacter::SprintStart);
	PlayerInputComponent->BindAction("Sprint", IE_Released, this, &APlayerCharacter::SprintEnd);

	/**Setup all the Axis for the controller and the keyboard*/
	PlayerInputComponent->BindAxis("Move Forward", this, &APlayerCharacter::MoveForward);
	PlayerInputComponent->BindAxis("Move Right", this, &APlayerCharacter::MoveRight);
	
	/**Setup the camera movement for mouse*/
	PlayerInputComponent->BindAxis("Turn", this, &APlayerCharacter::Turn);
	PlayerInputComponent->BindAxis("LookUp", this, &APlayerCharacter::LookUp);

	/**Setup the camera movement for controller*/
	PlayerInputComponent->BindAxis("TurnRate", this, &APlayerCharacter::TrunRate);
	PlayerInputComponent->BindAxis("LookUpRate", this, &APlayerCharacter::LookUpRate);

	/**Setup the attacking Event*/
	PlayerInputComponent->BindAction("Attack", IE_Pressed, this,  &APlayerCharacter::AttackInput);
	PlayerInputComponent->BindAction("Attack", IE_Released, this, &APlayerCharacter::AttackEnd);

	/**Setup pause event*/
	PlayerInputComponent->BindAction("Pause", IE_Pressed, this, &APlayerCharacter::Pause);
}

void APlayerCharacter::AttackInput()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT(__FUNCTION__));
	}

	// generate a random montage between 1 and 2
	int32 MontageSactionIndax = rand() % 3 + 1;

	// create montage section
	FString MontageSection = "Start_" + FString::FromInt(MontageSactionIndax);

	PlayAnimMontage(MeleeLightAttackAinmation, 1.f, FName(*MontageSection));

}

void APlayerCharacter::AttackStart()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT(__FUNCTION__));
	}

	SwordCollision->SetCollisionProfileName("Weapon");
	SwordCollision->SetNotifyRigidBodyCollision(true);
}

void APlayerCharacter::AttackEnd()
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Emerald, TEXT(__FUNCTION__));
	}

	SwordCollision->SetCollisionProfileName("NoCollision");
	SwordCollision->SetNotifyRigidBodyCollision(false);
}

void APlayerCharacter::OnHitAttack(UPrimitiveComponent* HitComponent, AActor* OtherActor,
					   UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, Hit.GetActor()->GetName());
	}
	
	if (bCanBeDamaged)
	{
		
	}

}
