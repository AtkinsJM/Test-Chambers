// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Components/BoxComponent.h"
#include "Components/SphereComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Math/Vector.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

#define OUT

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

	RollingSpeed = 360.0f;

	RollCue = nullptr;

	//InteractionVolume->OnComponentBeginOverlap.AddDynamic(this, &AAnimalCharacter::OnBeginOverlap);
	//InteractionVolume->OnComponentEndOverlap.AddDynamic(this, &AAnimalCharacter::OnEndOverlap);

}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	SetActorRotation(FRotator(0));

	Width = Mesh->GetRelativeScale3D().X * 100 / 2.0f;

	ForwardRotationPoint = FVector(Width, 0, -Width);
	BackwardRotationPoint = FVector(-Width, 0, -Width);
	LeftRotationPoint = FVector(0, -Width, -Width);
	RightRotationPoint = FVector(0, Width, -Width);
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	if (bIsRolling)
	{
		Roll(DeltaTime);
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
	// Get movement direction (x-y plane)
	RollingDirection = FVector(RotationPoint.X != 0 ? FMath::Abs(RotationPoint.X) / RotationPoint.X : 0, RotationPoint.Y != 0 ? FMath::Abs(RotationPoint.Y) / RotationPoint.Y : 0, 0);
	if (IsBlocked(RollingDirection)) { return; }
	bIsRolling = true;
	// Initialise rotation angle
	RotationAngle = 0.0f;
	// Get rotation origin (point/axis about which rotation occurs)
	RotationOrigin = GetActorLocation() + RotationPoint;
	
}


void APlayerCharacter::Roll(float DeltaTime)
{
	// Get change in angle for this frame
	float a = DeltaTime * RollingSpeed; 
	a = RotationAngle + a > 90.0f ? 90.0f - RotationAngle : a;
	RotationAngle += a;

	// Rotate position vector around axis and apply offset
	FVector CurrentPositionVector = GetActorLocation() - RotationOrigin;
	FVector Axis = FVector::CrossProduct(FVector(0, 0, 1), RollingDirection).GetSafeNormal();
	FVector NewPositionVector = CurrentPositionVector.RotateAngleAxis(a, Axis);
	FVector Offset = NewPositionVector - CurrentPositionVector;
	AddActorWorldOffset(Offset);

	// Calculate delta rotation and apply
	FQuat DeltaRotation = FQuat(FRotator(RollingDirection.X * -a, 0, RollingDirection.Y * a));
	AddActorWorldRotation(DeltaRotation);
	
	// End roll once 90 degrees reached.
	if (RotationAngle >= 90.0f)
	{
		if (RollCue)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), RollCue);
		}
		bIsRolling = false;
	}
}

bool APlayerCharacter::IsBlocked(FVector Direction)
{
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByChannel(OUT HitResult, GetActorLocation(), GetActorLocation() + (Direction * Width * 2), ECollisionChannel::ECC_WorldStatic))
	{
		UE_LOG(LogTemp, Warning, TEXT("Hit: %s"), *HitResult.Actor->GetName());
		return true;
	}
	return false;

	/*
	RaycastHit hit;
	if (Physics.Raycast(transform.position, dir, out hit, bounds.extents.x * 2))
	{
		if (!hit.collider.isTrigger)
		{
			return true;
		}
	}
	return false;
	*/
}