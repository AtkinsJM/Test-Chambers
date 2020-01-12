// Fill out your copyright notice in the Description page of Project Settings.


#include "Interactable.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
AInteractable::AInteractable()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<UBoxComponent>(TEXT("Root"));
	RootComponent = Root;
	Root->SetCollisionProfileName("Interactable");

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);
}

// Called when the game starts or when spawned
void AInteractable::BeginPlay()
{
	Super::BeginPlay();
	
	GetComponents<UStaticMeshComponent>(MeshesToHighlight, true);
}

// Called every frame
void AInteractable::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AInteractable::Interact(AActor * OtherActor)
{
	if (InteractCue)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), InteractCue);
	}
}

void AInteractable::ToggleHighlight(bool Value)
{
	if (MeshesToHighlight.Num() == 0) { return; }
	for (UStaticMeshComponent* Mesh : MeshesToHighlight)
	{
		Mesh->SetRenderCustomDepth(Value);
	}
}
