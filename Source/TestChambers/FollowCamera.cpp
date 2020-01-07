// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowCamera.h"
#include "Camera/CameraComponent.h"

// Sets default values
AFollowCamera::AFollowCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraRotation = FRotator(-38.0f, -45.0f, 0);

	DistanceFromTarget = 1000.0f;

	TargetToFollow = nullptr;
}

// Called when the game starts or when spawned
void AFollowCamera::BeginPlay()
{
	Super::BeginPlay();
	SetActorRotation(CameraRotation);
}

// Called every frame
void AFollowCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FollowTarget();
}

void AFollowCamera::FollowTarget()
{
	if (!TargetToFollow) { return; }
	
	FVector TargetPosition = TargetToFollow->GetActorLocation();
	float LateralDistance = DistanceFromTarget * FMath::Cos(FMath::DegreesToRadians(GetActorRotation().Pitch));
	float XOffset = LateralDistance * FMath::Cos(FMath::DegreesToRadians(FMath::Abs(GetActorRotation().Yaw)));
	float YOffset = LateralDistance * FMath::Sin(FMath::DegreesToRadians(FMath::Abs(GetActorRotation().Yaw)));
	// TODO: adjust z offset to avoid bumpiness when character is rolling
	float ZOffset = DistanceFromTarget * FMath::Sin(FMath::DegreesToRadians(FMath::Abs(GetActorRotation().Pitch)));
	FVector WantedPosition = FVector(TargetPosition.X - XOffset, TargetPosition.Y + YOffset, TargetPosition.Z + ZOffset);

	SetActorLocation(WantedPosition)
}

