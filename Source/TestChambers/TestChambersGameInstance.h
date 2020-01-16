// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/GameInstance.h"
#include "TestChambersGameInstance.generated.h"

/**
 * 
 */
UCLASS()
class TESTCHAMBERS_API UTestChambersGameInstance : public UGameInstance
{
	GENERATED_BODY()
	
public:
	UTestChambersGameInstance();

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	//bool bIsPaused;

	bool bIsNewLevel;

	bool bIsNewGame;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Data")
	bool bIsTransitioning;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	float TransitionDelay;

public:
	virtual void OnStart() override;
	
	virtual void LoadComplete(const float LoadTime, const FString& MapName) override;

	void SaveGame(FString SlotName);
	class UTestChambersSaveGame* LoadGame(FString SlotName);

	//void FinishSaveLoad();

	void StartLoadLevel(FString LevelName);

	void LoadLevel();

	void QuitGame();

	//FORCEINLINE void TogglePause() { SetPauseState(!bIsPaused); }

	//UFUNCTION(BlueprintCallable)
	//void SetPauseState(bool val);
private:

	FTimerHandle TransitionTimerHandle;

	FString LevelToLoad;

	FString CurrentLevelName;
};
