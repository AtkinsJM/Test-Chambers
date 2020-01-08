// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Interactable.h"
#include "KeyType.h"
#include "Door.generated.h"

/**
 * 
 */
UCLASS()
class TESTCHAMBERS_API ADoor : public AInteractable
{
	GENERATED_BODY()
	
public:
	ADoor();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	EKeyType RequiredKeyType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* DoorLockedCue;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* DoorUnlockedCue;

protected:

public:
	virtual void Interact(AActor* OtherActor) override;

	EKeyType GetRequiredKeyType() { return RequiredKeyType; }

	void Unlock();

private:
};
