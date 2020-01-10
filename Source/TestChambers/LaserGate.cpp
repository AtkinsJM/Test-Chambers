// Fill out your copyright notice in the Description page of Project Settings.


#include "LaserGate.h"
#include "Components/BoxComponent.h"
#include "Particles/ParticleSystemComponent.h"

// Sets default values
ALaserGate::ALaserGate()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = Root;
	Root->SetCollisionProfileName("BlockAll");

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));
	ParticleSystem->SetupAttachment(Root);

	bIsGateActive = true;
}

// Called when the game starts or when spawned
void ALaserGate::BeginPlay()
{
	Super::BeginPlay();
	
	if (!bIsGateActive)
	{
		Root->SetCollisionProfileName("NoCollision");
		ParticleSystem->Deactivate();
	}
}

// Called every frame
void ALaserGate::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ALaserGate::ToggleGate()
{
	bIsGateActive = !bIsGateActive;
	if (bIsGateActive)
	{
		Root->SetCollisionProfileName("BlockAll");
		ParticleSystem->Activate();
	}
	else
	{
		Root->SetCollisionProfileName("NoCollision");
		ParticleSystem->Deactivate();
	}
}

