// Fill out your copyright notice in the Description page of Project Settings.


#include "Pickup.h"
#include "Components/StaticMeshComponent.h"
#include "Components/SphereComponent.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

// Sets default values
APickup::APickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	Root = CreateDefaultSubobject<USphereComponent>(TEXT("Root"));
	RootComponent = Root;
	Root->SetCollisionEnabled(ECollisionEnabled::QueryOnly);
	Root->SetCollisionResponseToAllChannels(ECollisionResponse::ECR_Overlap);

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);
	Mesh->SetCollisionEnabled(ECollisionEnabled::NoCollision);

	bRotates = false;
	bFloats = false;

	RotationRate = 1.0f;
	Amplitude = 50.0f;
	Frequency = 1.0f;
}

// Called when the game starts or when spawned
void APickup::BeginPlay()
{
	Super::BeginPlay();
	
	Mesh->OnComponentHit.AddDynamic(this, &APickup::OnHit);
}

// Called every frame
void APickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (bFloats)
	{
		FVector RelativeLocation = FVector(0, 0, FMath::Sin(2 * PI * GetWorld()->GetTimeSeconds() * Frequency) * Amplitude);
		Mesh->SetRelativeLocation(RelativeLocation);
	}
	if (bRotates)
	{
		FRotator Rotation = FRotator(0, RotationRate * DeltaTime, 0);
		Mesh->AddRelativeRotation(Rotation);
	}
}

void APickup::PickedUpBy(AActor* OtherActor)
{
	if (PickupCue)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), PickupCue);
	}
	Destroy();
}

void APickup::OnHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit)
{

}

