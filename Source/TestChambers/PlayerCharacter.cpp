// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"

// Sets default values
APlayerCharacter::APlayerCharacter()
{
 	// Set this character to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Root = CreateDefaultSubobject<USceneComponent>(TEXT("Root"));
	RootComponent = Root;

	Mesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Mesh"));
	Mesh->SetupAttachment(Root);

	BoxCollider = CreateDefaultSubobject<UBoxComponent>(TEXT("Box Collider"));
	BoxCollider->SetupAttachment(Mesh);

	InteractionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Volume"));
	InteractionVolume->SetupAttachment(Root);

	//InteractionVolume->OnComponentBeginOverlap.AddDynamic(this, &AAnimalCharacter::OnBeginOverlap);
	//InteractionVolume->OnComponentEndOverlap.AddDynamic(this, &AAnimalCharacter::OnEndOverlap);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(FRotator(0));

	Width = Mesh->GetRelativeScale3D().X * 100 / 2.0f;
	UE_LOG(LogTemp, Warning, TEXT("Width: %f"), Width);

	ForwardRotationPoint = FVector(Width, 0, -Width);
	BackwardRotationPoint = FVector(-Width, 0, -Width);
	LeftRotationPoint = FVector(0, -Width, -Width);
	RightRotationPoint = FVector(0, Width, -Width);

	DistanceFromOrigin = FMath::Sqrt(Width * Width * 2);

	UE_LOG(LogTemp, Warning, TEXT("Distance from origin: %f"), DistanceFromOrigin);

	UE_LOG(LogTemp, Warning, TEXT("Player pos: %s"), *GetActorLocation().ToString());
	UE_LOG(LogTemp, Warning, TEXT("Forward rot pos: %s"), *ForwardRotationPoint.ToString());
	UE_LOG(LogTemp, Warning, TEXT("Right rot pos: %s"), *RightRotationPoint.ToString());
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsRolling)
	{
		if (RotationAngle < 90.0f)
		{
			Roll(DeltaTime);
		}
		return;
	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void APlayerCharacter::StartRolling(FVector RotationPoint)
{
	bIsRolling = true;
	// Initialise rotation angle
	RotationAngle = 0.0f;
	// Get rotation origin (point/axis about which rotation occurs)
	RotationOrigin = GetActorLocation() + RotationPoint;
	// Get movement direction (x-y plane)
	RollingDirection = FVector(RotationPoint.X != 0 ? FMath::Abs(RotationPoint.X) / RotationPoint.X : 0, RotationPoint.Y != 0 ? FMath::Abs(RotationPoint.Y) / RotationPoint.Y : 0, 0);
}


void APlayerCharacter::Roll(float DeltaTime)
{
	// Get change in angle for this frame
	float a = DeltaTime * 100; //speed
	RotationAngle += a;
	RotationAngle = RotationAngle > 90.0f ? 90.0f : RotationAngle;
	float OffsetAngle = 45.0f + RotationAngle;

	FVector SpatialOffset = FVector(DistanceFromOrigin * FMath::Cos(FMath::DegreesToRadians(OffsetAngle)) * -RollingDirection.X,
									DistanceFromOrigin * FMath::Cos(FMath::DegreesToRadians(OffsetAngle)) * -RollingDirection.Y,
									DistanceFromOrigin * FMath::Sin(FMath::DegreesToRadians(OffsetAngle)));
	SetActorLocation(RotationOrigin + SpatialOffset);


	FRotator RotationToApply = FRotator(RollingDirection.X * -a, 0, RollingDirection.Y * a);
	SetActorRotation(GetActorRotation() + RotationToApply);

	if (RotationAngle >= 90.0f)
	{
		// Finish rolling by zeroing out rotation
		SetActorRotation(FRotator(0));
		bIsRolling = false;
	}
}

