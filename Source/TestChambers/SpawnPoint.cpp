// Fill out your copyright notice in the Description page of Project Settings.


#include "SpawnPoint.h"
#include "Components/SceneComponent.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
ASpawnPoint::ASpawnPoint()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	BoxComponent = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxComponent->SetupAttachment(Root);
	BoxComponent->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Box Mesh"));
	Mesh->SetupAttachment(Root);
}

// Called when the game starts or when spawned
void ASpawnPoint::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ASpawnPoint::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

FVector ASpawnPoint::GetSpawnLocation()
{
	return BoxComponent->GetComponentLocation();
}

