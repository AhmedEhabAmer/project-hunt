// Fill out your copyright notice in the Description page of Project Settings.


#include "Spawner.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "HuntAICharacter.h"
#include "TimerManager.h"

// Sets default values
ASpawner::ASpawner()
{
 
  SpawnerMesh = CreateDefaultSubobject<UStaticMeshComponent>("Spawner Mesh");
  SpawnerMesh->SetupAttachment(RootComponent);

  SpwanerCollison = CreateDefaultSubobject<UBoxComponent>("Spawner Collision");
  SpwanerCollison->SetupAttachment(SpawnerMesh);
	
  SpawnerTime = 1.f;
}

// Called when the game starts or when spawned
void ASpawner::BeginPlay()
{
	Super::BeginPlay();

	if (bHideInGame)
	{
		DisableActor();
	}
	GetSpwanTime();
}

void ASpawner::GetSpwanTime()
{
	GetWorldTimerManager().SetTimer(SpwanTimerHandle, this, &ASpawner::SpawnerCounter, SpawnerTime, true);
}

void ASpawner::SpawnerCounter()
{
 	TArray<AHuntAICharacter*> EnemyCharacterCounter;
	//EnemyCharacterCounter.SetNum();

	//AHuntAICharacter* EnemyNum = Cast<AHuntAICharacter>(GetWorld()->GetNumPawns());


	for (int i = 0; i != 1; ++i)
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

	AHuntAICharacter* const EnemyChar = GetWorld()->SpawnActor<AHuntAICharacter>(AICharacter, Loc, Rot, SpawnParams);
	if (EnemyChar)
	{
		EnemyChar->SpawnDefaultController();
	}
}

void ASpawner::DisableActor()
{
	SetActorHiddenInGame(true);
	SetActorEnableCollision(false);
	SetActorTickEnabled(false);
}