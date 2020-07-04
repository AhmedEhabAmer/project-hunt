// Fill out your copyright notice in the Description page of Project Settings.


#include "HuntAICharacter.h"
#include "HuntAIController.h"
#include "BeHaviorTree/BehaviorTree.h"
#include "perception/PawnSensingComponent.h"
#include "Components/BoxComponent.h"
#include "TimerManager.h"

// Sets default values
AHuntAICharacter::AHuntAICharacter()
{
	/*Initialize senses*/
	PawnSensingComp = CreateDefaultSubobject<UPawnSensingComponent>("PawnSensingComp");
	PawnSensingComp->SetPeripheralVisionAngle(90.f);

}

// Called when the game starts or when spawned
void AHuntAICharacter::BeginPlay()
{
	Super::BeginPlay();
	
	/**Setup the Heath to be ready if damage event starts*/
	FullHealth = 100.f;
	Health = FullHealth;
	HealthPrecentage = 1.f;
	bCanBeDamaged = true;

	if (PawnSensingComp)
	{
		PawnSensingComp->OnSeePawn.AddDynamic(this, &AHuntAICharacter::OnPlayerCaught);
	}

}

float AHuntAICharacter::GetHealth()
{
	return HealthPrecentage;
}

void AHuntAICharacter::SetDamageState()
{	
	bCanBeDamaged = true;
}

void AHuntAICharacter::DamageTimer()
{
	GetWorldTimerManager().SetTimer(DamageTimerHandle, this,
	&AHuntAICharacter::SetDamageState, 1.0f, false);
}

float AHuntAICharacter::TakeDamage(float DamageAmount, FDamageEvent const& DamageEvent, AController* EventInstigator, AActor* DamageCauser)
{
	bCanBeDamaged = false;
	UpdateHealth(-DamageAmount);
	DamageTimer();
	return DamageAmount;
}

void AHuntAICharacter::UpdateHealth(float HealthChange)
{
	Health += HealthChange;
	Health = FMath::Clamp(Health, 0.0f, FullHealth);
	HealthPrecentage = Health / FullHealth;
	
	if (GEngine)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("%f"), HealthPrecentage));
	}

	if (HealthPrecentage <= 0.f)
	{
		Destroy();
	}
}

void AHuntAICharacter::OnPlayerCaught(APawn* InPawn)
{

	/*Get a reference to the player controller*/
	AHuntAIController* AIController = Cast<AHuntAIController>(GetController());

	if (AIController)
	{
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("You have been caught"));
		AIController->SetPlayerCaught(InPawn);
	}
}

// Called to bind functionality to input
void AHuntAICharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}
