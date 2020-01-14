// Fill out your copyright notice in the Description page of Project Settings.

#include "MovingPlatform.h"
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
		FVector NewLocation = FMath::VInterpConstantTo(GetActorLocation(), TargetLocation, DeltaTime, MovementSpeed);
		MovePlatformTo(NewLocation);
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
	PassengerOffset = Passenger->GetActorLocation() - GetActorLocation();
	CurrentWaypointIndex = (CurrentWaypointIndex + 1) % WaypointLocations.Num();
	TargetLocation = WaypointLocations[CurrentWaypointIndex];
	bIsMoving = true;
}

void AMovingPlatform::MovePlatformTo(FVector NewLocation)
{
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
