// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowCamera.h"
#include "Camera/CameraComponent.h"

#define OUT

// Sets default values
AFollowCamera::AFollowCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	CameraRotation = FRotator(-38.0f, -45.0f, 0);

	DistanceFromTarget = 1000.0f;

	TargetToFollow = nullptr;

	FollowSpeed = 5.0f;
}

// Called when the game starts or when spawned
void AFollowCamera::BeginPlay()
{
	Super::BeginPlay();
}

// Called every frame
void AFollowCamera::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	FollowTarget(DeltaTime);
}

void AFollowCamera::FollowTarget(float DeltaTime)
{
	if (!TargetToFollow) { return; }
	
	FVector TargetPosition;

	FVector Extent;
	TargetToFollow->GetActorBounds(false, OUT TargetPosition, OUT Extent);

	TargetPosition.Z = TargetPosition.Z + ((TargetExtents.Z - Extent.Z) /2.0f);

	FVector WantedPosition = TargetPosition + Offset;

	SetActorLocation(FMath::VInterpTo(GetActorLocation(), WantedPosition, DeltaTime, FollowSpeed));
}

void AFollowCamera::SetTarget(AActor * Target)
{
	TargetToFollow = Target;

	SetActorRotation(CameraRotation);

	float LateralDistance = DistanceFromTarget * FMath::Cos(FMath::DegreesToRadians(GetActorRotation().Pitch));
	float XOffset = LateralDistance * FMath::Cos(FMath::DegreesToRadians(FMath::Abs(GetActorRotation().Yaw)));
	float YOffset = LateralDistance * FMath::Sin(FMath::DegreesToRadians(FMath::Abs(GetActorRotation().Yaw)));
	float ZOffset = DistanceFromTarget * FMath::Sin(FMath::DegreesToRadians(FMath::Abs(GetActorRotation().Pitch)));

	Offset = FVector(-XOffset, YOffset, ZOffset);

	FVector TargetPosition;

	TargetToFollow->GetActorBounds(false, OUT TargetPosition, OUT TargetExtents);

	FVector WantedPosition = TargetPosition + Offset;
	SetActorLocation(WantedPosition);	
}

