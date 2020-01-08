// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "PlayerCharacter.h"
#include "FollowCamera.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"

APlayerCharacterController::APlayerCharacterController()
{
	bIsRolling = false;

	FollowCamera = nullptr;
}

void APlayerCharacterController::SetupInputComponent()
{
	Super::SetupInputComponent();
	
	InputComponent->BindAxis("ForwardMovement", this, &APlayerCharacterController::MoveForward);
	InputComponent->BindAxis(TEXT("SidewaysMovement"), this, &APlayerCharacterController::MoveSideways);

}

void APlayerCharacterController::OnPossess(APawn * Pawn)
{
	Super::OnPossess(Pawn);

	PlayerCharacter = Cast<APlayerCharacter>(Pawn);

	if (!FollowCamera)
	{
		AssignCamera();
	}
	else
	{
		FollowCamera->SetTarget(PlayerCharacter);
	}
}

void APlayerCharacterController::OnUnPossess()
{
	Super::OnUnPossess();

}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	
	if (!FollowCamera)
	{
		AssignCamera();
	}
	
	// Finds all playable (animal) characters in the world and places them in an array for swapping character.
	//FindPlayableCharacters();
	/*
	AAnimalCharacter* CurrentCharacter = Cast<AAnimalCharacter>(GetPawn());
	if (CurrentCharacter)
	{
		PlayableCharacters.Find(CurrentCharacter, OUT PossessedCharacterIndex);
	}
	*/

	/*
	if (HUDOverlayAsset != nullptr)
	{
		HUDOverlay = CreateWidget<UUserWidget>(this, HUDOverlayAsset);
		HUDOverlay->AddToViewport();
		HUDOverlay->SetVisibility(ESlateVisibility::Visible);
	}
	*/
}

void APlayerCharacterController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void APlayerCharacterController::AssignCamera()
{
	FollowCamera = Cast<AFollowCamera>(UGameplayStatics::GetActorOfClass(GetWorld(), FollowCameraClass));
	if (FollowCamera && PlayerCharacter)
	{
		SetViewTarget(FollowCamera);
		FollowCamera->SetTarget(PlayerCharacter);
	}
}

void APlayerCharacterController::MoveForward(float Value)
{
	if (!PlayerCharacter) { return; }
	if (PlayerCharacter->IsRolling() || Value == 0.0f) { return; }
	PlayerCharacter->StartRolling(Value > 0 ? PlayerCharacter->ForwardRotationPoint : PlayerCharacter->BackwardRotationPoint);
}

void APlayerCharacterController::MoveSideways(float Value)
{
	if (!PlayerCharacter) { return; }
	if (PlayerCharacter->IsRolling() || Value == 0.0f) { return; }
	PlayerCharacter->StartRolling(Value > 0 ? PlayerCharacter->RightRotationPoint : PlayerCharacter->LeftRotationPoint);
}
