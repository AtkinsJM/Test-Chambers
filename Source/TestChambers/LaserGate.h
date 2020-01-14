// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "LaserGate.generated.h"

UCLASS()
class TESTCHAMBERS_API ALaserGate : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ALaserGate();
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UParticleSystemComponent* ParticleSystem;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UAudioComponent* AudioComponent;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* LaserGateHumCue;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	bool bIsGateActive;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void ToggleGate();

private:

};
