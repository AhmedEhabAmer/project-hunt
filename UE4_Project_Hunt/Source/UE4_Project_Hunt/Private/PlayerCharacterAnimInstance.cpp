// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterAnimInstance.h"
#include "PlayerCharacter.h"
#include "GameFramework/PawnMovementComponent.h"

UPlayerCharacterAnimInstance::UPlayerCharacterAnimInstance()
{
	PlayerCharacterSpeed = 0.f;
	BlendspaceDirection = 0.f;
	bIsInAir = false;
	bIsPlayerCharacterMoving = false;
	bIsPlayerCharacterJogging = false;
	bIsPlayerCharacterSprinting = false;
	bIsPlayerCharacterCrouching = false;
	bHasKatana = false;
}

void UPlayerCharacterAnimInstance::NativeInitializeAnimation()
{
	Super::NativeInitializeAnimation();
	/** Cache The Pawn */
	Owner = TryGetPawnOwner();
}

void UPlayerCharacterAnimInstance::NativeUpdateAnimation(float DeltaTimeX)
{
	Super::NativeUpdateAnimation(DeltaTimeX);
	if (!Owner)
	{
		return;
	}

	if (Owner->IsA(APlayerCharacter::StaticClass()))
	{
		APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Owner);
		if (PlayerCharacter)
		{
			PlayerCharacterSpeed = PlayerCharacter->GetVelocity().Size();
			bIsPlayerCharacterMoving = PlayerCharacter->GetVelocity().Size() > 0 ? true : false;
			bIsPlayerCharacterJogging = PlayerCharacter->GetVelocity().Size() > 170 ? true : false;
			bIsPlayerCharacterSprinting = PlayerCharacter->GetVelocity().Size() > 270 ? true : false;
			bIsInAir = PlayerCharacter->GetMovementComponent()->IsFalling();
			bIsPlayerCharacterCrouching = PlayerCharacter->GetMovementComponent()->IsCrouching();

		}
	}
}

