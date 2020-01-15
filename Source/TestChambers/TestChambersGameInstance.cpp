// Fill out your copyright notice in the Description page of Project Settings.


#include "TestChambersGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"

UTestChambersGameInstance::UTestChambersGameInstance()
{
	LevelToLoad = "";
	TransitionDelay = 1.0f;
}

void UTestChambersGameInstance::StartLoadLevel(FString LevelName)
{
	if (LevelName == "") { return; }
	LevelToLoad = LevelName;
	bIsTransitioning = true;
	if (LevelToLoad == "Quit")
	{
		UE_LOG(LogTemp, Warning, TEXT("Waiting to quit..."));
		GetWorld()->GetTimerManager().SetTimer(TransitionTimerHandle, this, &UTestChambersGameInstance::QuitGame, TransitionDelay, false);
	}
	else
	{
		UE_LOG(LogTemp, Warning, TEXT("Waiting to load level..."));
		GetWorld()->GetTimerManager().SetTimer(TransitionTimerHandle, this, &UTestChambersGameInstance::LoadLevel, TransitionDelay, false);
	}
}

void UTestChambersGameInstance::LoadLevel()
{
	UE_LOG(LogTemp, Warning, TEXT("Loading level..."));
	if (LevelToLoad == "") { return; }
	bIsTransitioning = false;
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelToLoad));
}

void UTestChambersGameInstance::QuitGame()
{
	UE_LOG(LogTemp, Warning, TEXT("Quitting..."));
	if (LevelToLoad == "") { return; }
	bIsTransitioning = false;
	TEnumAsByte< EQuitPreference::Type > QuitPreference;
	UKismetSystemLibrary::QuitGame(GetWorld(), GetPrimaryPlayerController(), QuitPreference, false);
}