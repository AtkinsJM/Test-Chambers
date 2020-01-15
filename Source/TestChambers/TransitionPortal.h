// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Portal.h"
#include "TransitionPortal.generated.h"

/**
 * 
 */
UCLASS()
class TESTCHAMBERS_API ATransitionPortal : public APortal
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	ATransitionPortal();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties")
	FString LevelToLoad;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Teleport() override;

	virtual void Activate(AActor* Activator) override;

};
