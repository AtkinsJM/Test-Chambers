// Fill out your copyright notice in the Description page of Project Settings.


#include "Portal.h"
#include "Particles/ParticleSystemComponent.h"
#include "PlayerCharacter.h"

APortal::APortal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));
	ParticleSystem->SetupAttachment(Root);

	TeleportDelay = 1.0f;


	CharacterToTeleport = nullptr;

	bIsTeleporting = false;
}

// Called when the game starts or when spawned
void APortal::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void APortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APortal::Activate(AActor* Activator)
{
	Super::Activate(Activator);


}