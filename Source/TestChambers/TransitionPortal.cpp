// Fill out your copyright notice in the Description page of Project Settings.


#include "TransitionPortal.h"
#include "PlayerCharacter.h"
#include "Engine/World.h"
#include "Kismet/GameplayStatics.h"
#include "TestChambersGameInstance.h"

// Sets default values
ATransitionPortal::ATransitionPortal()
{
	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	LevelToLoad = "";
}

// Called when the game starts or when spawned
void ATransitionPortal::BeginPlay()
{
	Super::BeginPlay();

}

// Called every frame
void ATransitionPortal::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ATransitionPortal::Activate(AActor* Activator)
{
	Super::Activate(Activator);

	if (bIsTeleporting || LevelToLoad == "") { return; }
	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(Activator);
	if (!PlayerCharacter) { return; }
	bIsTeleporting = true;
	CharacterToTeleport = PlayerCharacter;
	CharacterToTeleport->SetCanMove(false);
	GetWorld()->GetTimerManager().SetTimer(TeleportTimerHandle, this, &ATransitionPortal::Teleport, TeleportDelay, false);
}

void ATransitionPortal::Teleport()
{
	Super::Teleport();

	bIsTeleporting = false;
	// TODO: check level exists before attempting to open
	UTestChambersGameInstance* GameInstance = Cast<UTestChambersGameInstance>(GetGameInstance());
	if (GameInstance)
	{
		GameInstance->StartLoadLevel(LevelToLoad);
	}
}
