// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MovingPlatform.generated.h"

UCLASS()
class TESTCHAMBERS_API AMovingPlatform : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMovingPlatform();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UBoxComponent* Root;
	
	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* Mesh;

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
	
	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void SetNewDestination();

private:
	class APlayerCharacter* Passenger;

	bool bIsMoving;

	FTimerHandle PlatformTimerHandle;

	TArray<FVector> WaypointLocations;

	int32 CurrentWaypointIndex;

	FVector TargetLocation;

	FVector PassengerOffset;
};
