// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Activatable.h"
#include "Portal.generated.h"

/**
 * 
 */
UCLASS()
class TESTCHAMBERS_API APortal : public AActivatable
{
	GENERATED_BODY()
	
public:
	// Sets default values for this actor's properties
	APortal();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UParticleSystemComponent* ParticleSystem;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	float TeleportDelay;


	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* TeleportCue;

	class APlayerCharacter* CharacterToTeleport;

	FTimerHandle TeleportTimerHandle;

	bool bIsTeleporting;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	virtual void Activate(AActor* Activator) override;

private:
	
};
