// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "KeyType.h"
#include "PlayerCharacter.generated.h"

UCLASS()
class TESTCHAMBERS_API APlayerCharacter : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this character's properties
	APlayerCharacter();

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class USceneComponent* Root;

	UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	class UStaticMeshComponent* Mesh;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	//class UBoxComponent* BoxCollider;

	//UPROPERTY(VisibleAnywhere, BlueprintReadOnly, Category = "Components")
	//class USphereComponent* InteractionVolume;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Properties")
	float RollingSpeed;

	FVector ForwardRotationPoint;

	FVector BackwardRotationPoint;

	FVector LeftRotationPoint;

	FVector RightRotationPoint;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Sound")
	class USoundCue* RollCue;


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	void StartRolling(FVector RotationPoint);

	void Roll(float DeltaTime);

	void FinishRolling();

	FORCEINLINE bool IsRolling() { return bIsRolling; }

	bool IsBlocked(FVector Direction);

	UFUNCTION()
	virtual void OnBeginOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult);
	UFUNCTION()
	virtual void OnEndOverlap(UPrimitiveComponent* OverlappedComponent, AActor* OtherActor, UPrimitiveComponent* OtherComp, int32 OtherBodyIndex);

	void PickUp(class APickup* Pickup);

	void PickUpKey(class ADoorKey* Key);

	FString ConvertDecimalToBinary(int32 Decimal);

	class AInteractable* IsInteractablePresent();

	UFUNCTION(BlueprintCallable)
	FORCEINLINE AInteractable* GetInteractable() { return Interactable; }

	bool HasKey(EKeyType KeyType) {	return KeyFlags & static_cast<int>(KeyType); }

	void Interact();

	FORCEINLINE void SetCanMove(bool Value) { bCanMove = Value; }
	
	FORCEINLINE void SetInteractable(AInteractable* _Interactable) { Interactable = _Interactable; }

private:
	bool bIsRolling;
	bool bCanMove;

	float RotationAngle;

	FVector RotationOrigin;

	FVector RollingDirection;
	
	float Width;

	int32 KeyFlags;

	AInteractable* Interactable;
};
