 // Fill out your copyright notice in the Description page of Project Settings.


#include "DamageActor.h"
#include "Kismet/GameplayStatics.h"
#include "TimerManager.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ADamageActor::ADamageActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	
	MyBoxComponent = CreateDefaultSubobject<UBoxComponent>("Damage Box");
	MyBoxComponent->InitBoxExtent(BoxSize);
	RootComponent = MyBoxComponent;

	Particle = CreateDefaultSubobject<UParticleSystemComponent>("Particle");
	Particle->SetRelativeLocation(FVector(0.f, 0.f, 0.f));
	Particle->SetupAttachment(RootComponent);


	MyBoxComponent->OnComponentBeginOverlap.AddDynamic(this, &ADamageActor::OnOverlapBegin);
	MyBoxComponent->OnComponentEndOverlap.AddDynamic(this, &ADamageActor::OnOverlapEnd);

	bCanBeDamaged = false;

}

void ADamageActor::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep,
	const FHitResult& SweepResult)
{
	if ( (OtherActor != nullptr) && (OtherActor != this) && (OtherComp != nullptr) )
	{
		bCanBeDamaged = true;
		MyCharacter = Cast<AActor>(OtherActor);
		MyHit = SweepResult;
		GetWorldTimerManager().SetTimer(DamageTimerHandle, this, &ADamageActor::ApplyDamage, 2.2f,
		true, 0.0f);
	}
}
void ADamageActor::OnOverlapEnd(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor,
	class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex)
{
	bCanBeDamaged = false;
	GetWorldTimerManager().ClearTimer(DamageTimerHandle);
}

void ADamageActor::ApplyDamage()
{
	if (bCanBeDamaged)
	{
		UGameplayStatics::ApplyPointDamage(MyCharacter, 20.f, GetActorLocation(),
		MyHit, nullptr, this, FireDamageType);
	}
}