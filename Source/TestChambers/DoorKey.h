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

	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Properties")
	EKeyType KeyType;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	class UTexture2D* DisplayImage;

protected:

public:
	virtual void PickedUpBy(AActor* OtherActor) override;
	
	FORCEINLINE EKeyType GetKeyType() { return KeyType; }

	UFUNCTION(BlueprintCallable)
	FORCEINLINE UTexture2D* GetDisplaImage() { return DisplayImage; }

private:

};
