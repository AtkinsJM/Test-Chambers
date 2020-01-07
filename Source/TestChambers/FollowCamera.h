// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Camera/CameraActor.h"
#include "FollowCamera.generated.h"

UCLASS()
class TESTCHAMBERS_API AFollowCamera : public ACameraActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AFollowCamera();

	AFollowCamera(AActor* Target);

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	FRotator CameraRotation;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	float DistanceFromTarget;

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties")
	AActor* TargetToFollow;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void FollowTarget();

	FORCEINLINE void SetTarget(AActor* Target) { TargetToFollow = Target; }

};
