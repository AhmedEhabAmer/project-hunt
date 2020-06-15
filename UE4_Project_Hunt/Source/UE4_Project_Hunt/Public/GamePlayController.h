// Fill out your copyright notice in the Description page of Project Settings.


#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerController.h"
#include "PlayerCharacter.h"
#include "GamePlayController.generated.h"

/* * Enum to see if the player still playing or no */
UENUM()
enum class EGamePlayState
{
	EPlying,
	EGameOver,
	EUnknown
};

UCLASS()
class UE4_PROJECT_HUNT_API AGamePlayController : public APlayerController
{
	GENERATED_BODY()

public:

	AGamePlayController();

	virtual void BeginPlay() override;

	virtual void Tick(float DeltaTime) override;


	APlayerCharacter* MyCharacther;

	UFUNCTION(BlueprintPure, Category = "Health")
		EGamePlayState GetCurrentState() const;

	void SetCurrentState(EGamePlayState NewState);

	APlayerCharacter* GetPlayerController();


private:

	EGamePlayState CurrentState;

	void HandleNewState(EGamePlayState NewState);

	void AimTowrdsCrosshir();

	bool GetLookVectorHitLocation(FVector HitDirection, FVector& HitLocation) const;

	bool GetSightRayHitLocation(FVector& HitLocation) const;

	bool GetLookDirection(FVector2D ScreenLocation, FVector& LookDirection) const;

	UPROPERTY(EditAnywhere, Category = "Line-Trace")
	float LineTraceRange;

	UPROPERTY(EditAnywhere, Category = "Line-Trace")
	float CrosshairXLocation;
	
	UPROPERTY(EditAnywhere, Category = "Line-Trace")
	float CrosshairYLocation;
};