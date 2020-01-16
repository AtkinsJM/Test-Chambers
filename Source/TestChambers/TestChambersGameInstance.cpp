// Fill out your copyright notice in the Description page of Project Settings.


#include "TestChambersGameInstance.h"
#include "Kismet/GameplayStatics.h"
#include "Engine/World.h"
#include "Kismet/KismetSystemLibrary.h"
#include "TestChambersSaveGame.h"

UTestChambersGameInstance::UTestChambersGameInstance()
{
	LevelToLoad = "";
	TransitionDelay = 1.0f;

	CurrentLevelName = "";
}

void UTestChambersGameInstance::OnStart()
{
	Super::OnStart();

	CurrentLevelName = GetWorld()->GetMapName();
	CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);
}

void UTestChambersGameInstance::LoadComplete(const float LoadTime, const FString & MapName)
{
	Super::LoadComplete(LoadTime, MapName);

	bIsTransitioning = false;

	CurrentLevelName = GetWorld()->GetMapName();
	CurrentLevelName.RemoveFromStart(GetWorld()->StreamingLevelsPrefix);

	if (CurrentLevelName != "Main_Menu")
	{
		SaveGame("Default");
	}
}

void UTestChambersGameInstance::SaveGame(FString SlotName)
{
	UTestChambersSaveGame* SaveGameInstance = Cast<UTestChambersSaveGame>(UGameplayStatics::CreateSaveGameObject(UTestChambersSaveGame::StaticClass()));

	if (!SaveGameInstance) { return; }
	
	SaveGameInstance->LevelName = CurrentLevelName;

	UGameplayStatics::SaveGameToSlot(SaveGameInstance, SlotName != "" ? SlotName : SaveGameInstance->SlotName, SaveGameInstance->UserIndex);
}

UTestChambersSaveGame * UTestChambersGameInstance::LoadGame(FString SlotName)
{
	UTestChambersSaveGame* LoadGameInstance = Cast<UTestChambersSaveGame>(UGameplayStatics::CreateSaveGameObject(UTestChambersSaveGame::StaticClass()));
	LoadGameInstance = Cast<UTestChambersSaveGame>(UGameplayStatics::LoadGameFromSlot(SlotName != "" ? SlotName : LoadGameInstance->SlotName, LoadGameInstance->UserIndex));

	return LoadGameInstance;
}

void UTestChambersGameInstance::StartLoadLevel(FString LevelName)
{
	if (LevelName == "") { return; }

	LevelToLoad = LevelName;

	if (LevelToLoad == "Quit")
	{
		bIsTransitioning = true;
		GetWorld()->GetTimerManager().SetTimer(TransitionTimerHandle, this, &UTestChambersGameInstance::QuitGame, TransitionDelay, false);
		return;
	}
	else if (LevelToLoad == "Saved")
	{
		UTestChambersSaveGame* LoadGameInstance = LoadGame("Default");

		// If saved game with specified slot name can't be found, don't try loading
		if (!LoadGameInstance) { return; }

		FString LevelName = LoadGameInstance->LevelName;
		if (LevelName != "")
		{
			LevelToLoad = LevelName;
		}		
	}
	bIsTransitioning = true;
	GetWorld()->GetTimerManager().SetTimer(TransitionTimerHandle, this, &UTestChambersGameInstance::LoadLevel, TransitionDelay, false);	
}

void UTestChambersGameInstance::LoadLevel()
{
	if (LevelToLoad == "") { return; }
	
	UGameplayStatics::OpenLevel(GetWorld(), FName(*LevelToLoad));
}

void UTestChambersGameInstance::QuitGame()
{
	if (CurrentLevelName != "Main_Menu")
	{
		SaveGame("Default");
	}
	TEnumAsByte< EQuitPreference::Type > QuitPreference;
	UKismetSystemLibrary::QuitGame(GetWorld(), GetPrimaryPlayerController(), QuitPreference, false);
}