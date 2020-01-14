// Fill out your copyright notice in the Description page of Project Settings.


#include "Activatable.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"

// Sets default values
AActivatable::AActivatable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionProfileName("OverlapOnlyPawn");

}

// Called when the game starts or when spawned
void AActivatable::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AActivatable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AActivatable::Activate(AActor * Activator)
{

}
