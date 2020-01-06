// Fill out your copyright notice in the Description page of Project Settings.


#include "PlayerCharacterController.h"
#include "PlayerCharacter.h"

APlayerCharacterController::APlayerCharacterController()
{
	bIsRolling = false;
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
}

void APlayerCharacterController::OnUnPossess()
{
	Super::OnUnPossess();

}

void APlayerCharacterController::BeginPlay()
{
	Super::BeginPlay();
	
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

void APlayerCharacterController::HandleMovement(float DeltaTime)
{
	//Handle movement and rotation
	if (!PlayerCharacter) { return; }

	

}

void APlayerCharacterController::MoveForward(float Value)
{
	if (!PlayerCharacter) { return; }
	if (PlayerCharacter->IsRolling() || Value < 0.5f) { return; }
	MovementVector = FVector2D(Value, 0);
	PlayerCharacter->StartRolling(Value > 0 ? PlayerCharacter->ForwardRotationPoint : PlayerCharacter->BackwardRotationPoint);
}

void APlayerCharacterController::MoveSideways(float Value)
{
	if (!PlayerCharacter) { return; }
	if (PlayerCharacter->IsRolling() || Value < 0.5f) { return; }
	MovementVector = FVector2D(0, Value);
	PlayerCharacter->StartRolling(Value > 0 ? PlayerCharacter->RightRotationPoint : PlayerCharacter->LeftRotationPoint);
}
