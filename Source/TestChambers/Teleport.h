// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Portal.h"
#include "Teleport.generated.h"

UCLASS()
class TESTCHAMBERS_API ATeleport : public APortal
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ATeleport();

	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties")
	class ASpawnPoint* SpawnPoint;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	void Teleport();

	virtual void Activate(AActor* Activator) override;

};
