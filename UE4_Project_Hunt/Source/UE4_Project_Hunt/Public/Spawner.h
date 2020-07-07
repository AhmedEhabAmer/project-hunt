// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "HuntAICharacter.h"
#include "Spawner.generated.h"

class UStaticMeshComponent;
class UBoxComponent;

UCLASS()
class UE4_PROJECT_HUNT_API ASpawner : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ASpawner();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	void Spawner();
	void SpawnerCounter();
	void DisableActor();

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Character To Spwan", meta = (AllowPrivateAccess = "true"))
	TSubclassOf<AActor> AICharacter;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Spanwer Mesh", meta = (AllowPrivateAcsess = "ture"))
	UStaticMeshComponent* SpawnerMesh;

	UPROPERTY(EditDefaultsOnly, BluePrintReadOnly, Category = "Spanwer Mesh", meta = (AllowPrivateAcsess = "ture"))
	UBoxComponent* SpwanerCollison;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Disable")
	bool bHideInGame;
	
};
