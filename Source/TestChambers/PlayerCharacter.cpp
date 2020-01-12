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
#include "Pickup.h"
#include "DoorKey.h"
#include "Interactable.h"

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
	Mesh->SetCollisionProfileName("Player");
	
	RollingSpeed = 360.0f;

	RollCue = nullptr;
	
	Interactable = nullptr;

	bCanMove = true;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();

	Mesh->OnComponentBeginOverlap.AddDynamic(this, &APlayerCharacter::OnBeginOverlap);
	Mesh->OnComponentEndOverlap.AddDynamic(this, &APlayerCharacter::OnEndOverlap);

	SetActorRotation(FRotator(0));

	KeyFlags = 0;

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
	else
	{

	}
}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}


void APlayerCharacter::StartRolling(FVector RotationPoint)
{
	if (!bCanMove) { return; }

	if (Interactable)
	{
		Interactable->ToggleHighlight(false);
		Interactable = nullptr;
	}	

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
		FinishRolling();
	}
}

void APlayerCharacter::FinishRolling()
{
	if (RollCue)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), RollCue);
	}
	bIsRolling = false;
	Interactable = IsInteractablePresent();
	if (Interactable)
	{
		Interactable->ToggleHighlight(true);
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

void APlayerCharacter::OnBeginOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
{
	APickup* Pickup = Cast<APickup>(OtherActor);
	if (Pickup)
	{
		PickUp(Pickup);
	}
}

void APlayerCharacter::OnEndOverlap(UPrimitiveComponent * OverlappedComponent, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex)
{
}

void APlayerCharacter::PickUp(APickup* Pickup)
{
	ADoorKey* Key = Cast<ADoorKey>(Pickup);
	if (Key)
	{
		PickUpKey(Key);
	}
	Pickup->PickedUpBy(this);
}

void APlayerCharacter::PickUpKey(ADoorKey * Key)
{
	KeyFlags |= (int32)Key->GetKeyType();
	//FString FlagsBinary = ConvertDecimalToBinary(KeyFlags);
	//UE_LOG(LogTemp, Warning, TEXT("%s"), *FlagsBinary);
}

FString APlayerCharacter::ConvertDecimalToBinary(int32 Decimal)
{
	FString Sequence = "";
	int32 Remainder = 0;
	while (Decimal > 0)
	{
		Remainder = Decimal % 2;
		Sequence += FString::FromInt(Remainder);
		Decimal /= 2;
	}
	Sequence.ReverseString();
	return Sequence;
}

AInteractable * APlayerCharacter::IsInteractablePresent()
{
	FHitResult HitResult;
	if (GetWorld()->LineTraceSingleByProfile(OUT HitResult, GetActorLocation(), GetActorLocation() + FVector(2 * Width, 0, 0), "Interactable") ||
		GetWorld()->LineTraceSingleByProfile(OUT HitResult, GetActorLocation(), GetActorLocation() + FVector(-2 * Width, 0, 0), "Interactable") ||
		GetWorld()->LineTraceSingleByProfile(OUT HitResult, GetActorLocation(), GetActorLocation() + FVector(0, 2 * Width, 0), "Interactable") ||
		GetWorld()->LineTraceSingleByProfile(OUT HitResult, GetActorLocation(), GetActorLocation() + FVector(0, -2 * Width, 0), "Interactable"))
	{
		return Cast<AInteractable>(HitResult.Actor);
	}
	return nullptr;
}

void APlayerCharacter::Interact()
{
	if (!Interactable) { return; }
	Interactable->Interact(this);
}
