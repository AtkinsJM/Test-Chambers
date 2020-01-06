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

	ForwardRotationPoint = FVector(Mesh->GetRelativeScale3D().X * 100 / 2.0f, 0, 0);
	BackwardRotationPoint = FVector(-Mesh->GetRelativeScale3D().X * 100 / 2.0f, 0, 0);
	LeftRotationPoint = FVector(0, -Mesh->GetRelativeScale3D().Y * 100 / 2.0f, 0);
	RightRotationPoint = FVector(0, Mesh->GetRelativeScale3D().Y * 100 / 2.0f, 0);

	DistanceFromOrigin = FMath::Sqrt(FMath::Square(Mesh->GetRelativeScale3D().X / 2.0f) * FMath::Square(Mesh->GetRelativeScale3D().Y / 2.0f));

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
			Roll();
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
	RotationAngle = 0.0f;
	RotationOrigin = GetActorLocation() + RotationPoint;
	RollingDirection = FVector(RotationPoint.X != 0 ? FMath::Abs(RotationPoint.X) / RotationPoint.X : 0, RotationPoint.Y != 0 ? FMath::Abs(RotationPoint.Y) / RotationPoint.Y : 0, 0);
}


void APlayerCharacter::Roll()
{
	// Get change in angle
	float a = GetWorld()->DeltaTimeSeconds * 100;//speed; //rotationSpeed * (Time::GetSpeed() / 30.0f);
	RotationAngle += a;
	RotationAngle = RotationAngle > 90.0f ? 90.0f : RotationAngle;
	// Calculate angle between centre of entity and rotationOrigin
	float OffsetAngle = 45.0f + RotationAngle;
	// Calculate spacial offset between centre of entity and rotationOrigin
	//FVector Offset = FVector(DistanceFromOrigin * FMath::Cos(OffsetAngle) * -RollingDirection.X, DistanceFromOrigin * FMath::Sin(OffsetAngle), DistanceFromOrigin * FMath::Cos(OffsetAngle) * -RollingDirection.Z);
	//SetActorLocation(RotationOrigin + Offset);
	FRotator RotationToApply = FRotator(RollingDirection.X * -a, 0, RollingDirection.Y * a);
	SetActorRotation(GetActorRotation() + RotationToApply);
	
	if (RotationAngle >= 90.0f)
	{
		// Finish rolling by zeroing out rotation
		SetActorRotation(FRotator(0));
		bIsRolling = false;
	}
	
}

