// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/SaveGame.h"
#include "TestChambersSaveGame.generated.h"

/**
 * 
 */
UCLASS()
class TESTCHAMBERS_API UTestChambersSaveGame : public USaveGame
{
	GENERATED_BODY()

public:
	UTestChambersSaveGame();

	UPROPERTY(VisibleAnywhere, Category = "Basic")
	FString SlotName;

	UPROPERTY(VisibleAnywhere, Category = "Basic")
	uint32 UserIndex;

	UPROPERTY(VisibleAnywhere, Category = "Basic")
	FString LevelName;

	//UPROPERTY(VisibleAnywhere, Category = "Basic")
	//FCharacterStats CharacterStats;

	//UPROPERTY(VisibleAnywhere, Category = "Basic")
	//FWorldData WorldData;


};
