// Fill out your copyright notice in the Description page of Project Settings.


#include "Lever.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "PlayerCharacter.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"
#include "LaserGate.h"

ALever::ALever()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	
	Pivot = CreateDefaultSubobject<USceneComponent>(TEXT("Pivot"));

	LeverArmMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Lever Arm"));
	LeverArmMesh->SetupAttachment(Pivot);

	LeverPullCue = nullptr;
	LeverPushCue = nullptr;

	LeverPullSpeed = 5.0f;
}

void ALever::BeginPlay()
{
	Super::BeginPlay();
	LeverArmAngle = LeverArmMesh->GetComponentRotation().Roll;
}

void ALever::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	LeverArmMesh->SetRelativeRotation(FMath::RInterpTo(LeverArmMesh->GetRelativeRotation(), FRotator(0, 0, LeverArmAngle), DeltaTime, LeverPullSpeed));
}

void ALever::Interact(AActor * OtherActor)
{
	Super::Interact(OtherActor);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		PullLever();
	}
}

void ALever::PullLever()
{
	LeverArmAngle = -LeverArmAngle;

	if (LeverArmAngle > 0.0f)
	{
		if (LeverPullCue)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), LeverPullCue);
		}
	}
	else
	{
		if (LeverPushCue)
		{
			UGameplayStatics::PlaySound2D(GetWorld(), LeverPushCue);
		}
	}

	for (ALaserGate* LaserGate : ControlledGates)
	{
		LaserGate->ToggleGate();
	}
}
