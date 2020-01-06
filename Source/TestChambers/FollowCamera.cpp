// Fill out your copyright notice in the Description page of Project Settings.


#include "FollowCamera.h"
#include "Camera/CameraComponent.h"

// Sets default values
AFollowCamera::AFollowCamera()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// Create Follow Camera
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	// Attach camera to end of boom and let boom control its rotation
	Camera->SetupAttachment(GetRootComponent());
	//Camera->bUsePawnControlRotation = false;
	Camera->SetFieldOfView(10.0f);
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

}

