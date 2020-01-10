// Fill out your copyright notice in the Description page of Project Settings.


#include "Teleport.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
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

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = Root;
	
	ParticleSystem = CreateDefaultSubobject<UParticleSystemComponent>(TEXT("Particle System"));
	ParticleSystem->SetupAttachment(Root);
	
	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Cylinder Mesh"));
	Mesh->SetupAttachment(Root);

	TeleportDelay = 1.0f;

	SpawnPoint = nullptr;

	ActorToTeleport = nullptr;

	bIsTeleporting = false;
}

// Called when the game starts or when spawned
void ATeleport::BeginPlay()
{
	Super::BeginPlay();
	Root->OnComponentBeginOverlap.AddDynamic(this, &ATeleport::OnBeginOverlap);
	Root->OnComponentEndOverlap.AddDynamic(this, &ATeleport::OnEndOverlap);
}

// Called every frame
void ATeleport::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATeleport::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	if (bIsTeleporting || !SpawnPoint) { return; }
	bIsTeleporting = true;
	ActorToTeleport = OtherActor;
	GetWorld()->GetTimerManager().SetTimer(TeleportTimerHandle, this, &ATeleport::Teleport, TeleportDelay, false);
}

void ATeleport::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{

}

void ATeleport::Teleport()
{
	ActorToTeleport->SetActorLocation(SpawnPoint->GetSpawnLocation());

	if (TeleportCue)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), TeleportCue);
	}
	ActorToTeleport = nullptr;
	bIsTeleporting = false;
}
