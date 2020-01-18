// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Activatable.h"
#include "FloorSwitch.generated.h"

/**
 * 
 */
UCLASS()
class TESTCHAMBERS_API AFloorSwitch : public AActivatable
{
	GENERATED_BODY()

public:
	// Sets default values for this actor's properties
	AFloorSwitch();
	
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* SwitchCue;
	
	UPROPERTY(EditInstanceOnly, BlueprintReadOnly, Category = "Properties")
	class AForcefield* ForcefieldToToggle;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	class UMaterialInterface* PressedMaterial;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Activate(AActor* Activator) override;

	virtual void Press();

private:

};
