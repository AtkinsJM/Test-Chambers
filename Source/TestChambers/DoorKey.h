// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Pickup.h"
#include "DoorKey.generated.h"

UENUM(Meta = (Bitflags))
enum class EKeyType
{
	EKT_Red = 1 UMETA(DisplayName = "Red key"),
	EKT_Green = 2 UMETA(DisplayName = "Green key"),
	EKT_Blue = 4 UMETA(DisplayName = "Blue key"),
	EKT_Yellow = 8 UMETA(DisplayName = "Yellow key"),
	EKT_Orange = 16 UMETA(DisplayName = "Orange key"),
	EKT_Purple = 32 UMETA(DisplayName = "Purple key"),
};

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
