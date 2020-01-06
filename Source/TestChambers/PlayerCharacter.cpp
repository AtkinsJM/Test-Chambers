// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacter.h"
#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
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

	InteractionVolume = CreateDefaultSubobject<USphereComponent>(TEXT("Interaction Volume"));
	InteractionVolume->SetupAttachment(Root);

	//InteractionVolume->OnComponentBeginOverlap.AddDynamic(this, &AAnimalCharacter::OnBeginOverlap);
	//InteractionVolume->OnComponentEndOverlap.AddDynamic(this, &AAnimalCharacter::OnEndOverlap);

	DefaultCameraBoomLength = 300.0f;
	
	// Create Camera Boom
	CameraBoom = CreateDefaultSubobject<USpringArmComponent>(TEXT("Camera Boom"));
	CameraBoom->SetupAttachment(Root);
	CameraBoom->bUsePawnControlRotation = true;

	// Disabled because camera lag was annoying when possessing characters
	//CameraBoom->bEnableCameraLag = true;
	//CameraBoom->bEnableCameraRotationLag = true;

	// Create Follow Camera
	FollowCamera = CreateDefaultSubobject<UCameraComponent>(TEXT("Follow Camera"));
	// Attach camera to end of boom and let boom control its rotation
	FollowCamera->SetupAttachment(CameraBoom, USpringArmComponent::SocketName);
	FollowCamera->bUsePawnControlRotation = false;
}

// Called when the game starts or when spawned
void APlayerCharacter::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void APlayerCharacter::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

// Called to bind functionality to input
void APlayerCharacter::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

