// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleport.h"
#include "Particles/ParticleSystemComponent.h"
#include "PlayerCharacter.h"
#include "Engine/World.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "SpawnPoint.h"

// Sets default values
ATeleport::ATeleport()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
		
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));
	ParticleSystem->SetupAttachment(Root);

	TeleportDelay = 1.0f;

	SpawnPoint = nullptr;

	CharacterToTeleport = nullptr;

	bIsTeleporting = false;
}

// Called when the game starts or when spawned
void ATeleport::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleport::Teleport()
{
	CharacterToTeleport->SetActorLocation(SpawnPoint->GetSpawnLocation());

	if (TeleportCue)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), TeleportCue);
	}

	CharacterToTeleport->SetCanMove(true);
	CharacterToTeleport = nullptr;
	bIsTeleporting = false;
}

void ATeleport::Activate(AActor* Activator)
{
	Super::Activate(Activator);
	
	if (bIsTeleporting || !SpawnPoint) { return; }
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Activator);
	if (!PlayerCharacter) { return; }
	bIsTeleporting = true;
	CharacterToTeleport = PlayerCharacter;
	CharacterToTeleport->SetCanMove(false);
	GetWorld()->GetTimerManager().SetTimer(TeleportTimerHandle, this, &ATeleport::Teleport, TeleportDelay, false);
}