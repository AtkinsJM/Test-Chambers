// Fill out your copyright notice in the Description page of Project Settings.


#include "Forcefield.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "Components/AudioComponent.h"

// Sets default values
AForcefield::AForcefield()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	
	AudioComponent = CreateDefaultSubobject<UAudioComponent>(TEXT("Audio Component"));
	AudioComponent->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void AForcefield::BeginPlay()
{
	Super::BeginPlay();
	AudioComponent->Play();
}

// Called every frame
void AForcefield::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

