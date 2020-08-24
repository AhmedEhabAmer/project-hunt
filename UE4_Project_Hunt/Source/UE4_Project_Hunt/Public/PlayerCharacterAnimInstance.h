// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Animation/AnimInstance.h"
#include "PlayerCharacterAnimInstance.generated.h"


UCLASS()
class UE4_PROJECT_HUNT_API UPlayerCharacterAnimInstance : public UAnimInstance
{
	GENERATED_BODY()
	
public:
		/** If The Player Character Does not Have The Katana, Apply These Variables */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		float PlayerCharacterSpeed;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		float BlendspaceDirection;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		bool bIsInAir;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		bool bIsPlayerCharacterMoving;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		bool bIsPlayerCharacterSprinting;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		bool bIsPlayerCharacterJogging;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		bool bIsPlayerCharacterCrouching;

		/** If The Player Character Has The Katana, Apply These Variables */
	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Animation")
		bool bHasKatana;

		/** Main Functions */
	UPlayerCharacterAnimInstance();
	virtual void NativeInitializeAnimation() override;
	virtual void NativeUpdateAnimation(float DeltaTimeX) override;

private:
	APawn* Owner;
};
