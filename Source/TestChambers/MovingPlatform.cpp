// Fill out your copyright notice in the Description page of Project Settings.


#include "MovingPlatform.h"
#include "Components/BoxComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"
#include "Engine/World.h"

// Sets default values
AMovingPlatform::AMovingPlatform()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	bIsMoving = false;

	MovementDelay = 1.0f;
	MovementSpeed = 100.0f;

	CurrentWaypointIndex = 0;
}

// Called when the game starts or when spawned
void AMovingPlatform::BeginPlay()
{
	Super::BeginPlay();
	
	Passenger = nullptr;

	FVector StartPos = GetActorLocation();
	TargetLocation = StartPos;
	WaypointLocations.Add(StartPos);

	for (AActor* Waypoint : Waypoints)
	{
		WaypointLocations.Add(Waypoint->GetActorLocation());
	}

}

// Called every frame
void AMovingPlatform::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	if (!Passenger) { return; }

	if (bIsMoving)
	{
		UE_LOG(LogTemp, Warning, TEXT("Moving platform!"));

		FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), TargetLocation, DeltaTime, MovementSpeed);
		UE_LOG(LogTemp, Warning, TEXT("New location: %s"), *NewLocation.ToString());
		SetActorLocation(NewLocation);
		Passenger->SetActorLocation(NewLocation + PassengerOffset);

		float Distance = (NewLocation - TargetLocation).Size();
		if (Distance < 1.0f)
		{
			SetActorLocation(TargetLocation);
			Passenger->SetActorLocation(TargetLocation + PassengerOffset);
			bIsMoving = false;
			Passenger->SetCanMove(true);
			Passenger = nullptr;
		}
	}
}

void AMovingPlatform::Activate(AActor* Activator)
{
	Super::Activate(Activator);

	if (bIsMoving) { return; }
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Activator);
	if (!PlayerCharacter) { return; }

	Passenger = PlayerCharacter;
	Passenger->SetCanMove(false);
	PassengerOffset = Passenger->GetActorLocation() - GetActorLocation();

	GetWorld()->GetTimerManager().SetTimer(PlatformTimerHandle, this, &AMovingPlatform::SetNewDestination, MovementDelay, false);
}

void AMovingPlatform::SetNewDestination()
{
	UE_LOG(LogTemp, Warning, TEXT("Setting new destination for platform!"));
	PassengerOffset = Passenger->GetActorLocation() - GetActorLocation();
	CurrentWaypointIndex = (CurrentWaypointIndex + 1) % WaypointLocations.Num();
	TargetLocation = WaypointLocations[CurrentWaypointIndex];
	bIsMoving = true;
}