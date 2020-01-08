// Fill out your copyright notice in the Description page of Project Settings.


#include "Door.h"
#include "PlayerCharacter.h"
#include "Sound/SoundCue.h"
#include "Kismet/GameplayStatics.h"

ADoor::ADoor()
{

}

void ADoor::Interact(AActor * OtherActor)
{
	Super::Interact(OtherActor);

	APlayerCharacter* PlayerCharacter = Cast<APlayerCharacter>(OtherActor);
	if (PlayerCharacter)
	{
		if (PlayerCharacter->HasKey(RequiredKeyType))
		{
			Unlock();
		}
		else
		{
			if (DoorLockedCue)
			{
				UGameplayStatics::PlaySound2D(GetWorld(), DoorLockedCue);
			}
		}
	}
}

void ADoor::Unlock()
{
	if (DoorUnlockedCue)
	{
		UGameplayStatics::PlaySound2D(GetWorld(), DoorUnlockedCue);	
	}
	Destroy();
}
