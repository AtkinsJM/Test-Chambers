// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "KeyType.h"
#include "DoorKey.generated.h"



UCLASS()
class TESTCHAMBERS_API ADoorKey : public APickup
{
	GENERATED_BODY()
	
public:
	ADoorKey();

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Enum")
	EKeyType KeyType;

protected:

public:
	virtual void PickedUpBy(AActor* OtherActor) override;
	
	FORCEINLINE EKeyType GetKeyType() { return KeyType; }

private:

};
