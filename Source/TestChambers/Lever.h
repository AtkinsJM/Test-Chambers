// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "Lever.generated.h"

/**
 * 
 */
UCLASS()
class TESTCHAMBERS_API ALever : public AInteractable
{
	GENERATED_BODY()
	
public:
	ALever();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* Pivot;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* LeverArmMesh;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* LeverPullCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* LeverPushCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	float LeverPullSpeed;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties")
	TArray<class ALaserGate*> ControlledGates;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Interact(AActor* OtherActor) override;

	void PullLever();

private:

	float LeverArmAngle;
};
