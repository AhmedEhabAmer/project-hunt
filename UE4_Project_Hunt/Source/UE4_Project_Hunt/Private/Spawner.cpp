// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "HuntAICharacter.h"

// Sets default values
ASpawner::ASpawner()
{
 
  SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>("Spawner Mesh");
  SpawnerMesh->SetupAttachment(RootComponent);

  SpwanerCollison = CreateDefaultSubobject<UBoxComponent>("Spawner Collision");
  SpwanerCollison->SetupAttachment(SpawnerMesh);
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	if (bHideInGame)
	{
		DisableActor();
	}
	SpawnerCounter();
}

void ASpawner::SpawnerCounter()
{
	TArray<int> EnemyCount;
	EnemyCount.SetNum(10);

	for (int i = 0; i != EnemyCount.Num(); ++i)
	{
		Spawner();
		UE_LOG(LogTemp, Warning, TEXT("I'm Spwaning!"))
	}
}

void ASpawner::Spawner()
{
	FVector Loc;
	FRotator Rot;
	FActorSpawnParameters SpawnParams;
	SpawnParams.SpawnCollisionHandlingOverride = ESpawnActorCollisionHandlingMethod::AlwaysSpawn;

	Loc = GetActorLocation();

	AHuntAICharacter* EnemyChar = GetWorld()->SpawnActor<AHuntAICharacter>(AICharacter->StaticClass(), Loc, Rot, SpawnParams);
}

void ASpawner::DisableActor()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}