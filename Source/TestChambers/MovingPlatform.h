// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Activatable.h"
#include "MovingPlatform.generated.h"

/**
 *
 */
UCLASS()
class TESTCHAMBERS_API AMovingPlatform : public AActivatable
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Waypoints")
	TArray<AActor*> Waypoints;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	float MovementDelay;

	UPROPERTY(EditAnywhere, BlueprintReadOnly, Category = "Properties")
	float MovementSpeed;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Activate(AActor* Activator) override;

	void SetNewDestination();

	void MovePlatformTo(FVector NewLocation);

private:
	class APlayerCharacter* Passenger;

	bool bIsMoving;

	FTimerHandle PlatformTimerHandle;

	TArray<FVector> WaypointLocations;

	int32 CurrentWaypointIndex;

	FVector TargetLocation;

	FVector PassengerOffset;
};
