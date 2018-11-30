// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyTimePickup.h"
#include "MyTimePickupSpawnController.generated.h"

UCLASS()
class LEARNTODRIVEGAME_API AMyTimePickupSpawnController : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTimePickupSpawnController();

private:
	float generateX(float oldUsedX);									// Generates an X coord to use

	float generateY(float oldUsedY);									// Generates a Y coord to use

	bool isUsed(TArray<float> &oldArray, float numCheck);				// Checks if the value has been used before, by testing an array 

	float distanceBetween(float inOne, float inTwo);					// Checks the distance between points

	bool isOneGreater(float inOne, float inTwo);						// Checks if one value is greater than another

	TArray<float> oldX;													// An Array to Hold all the old X values

	TArray<float> oldY;													// An Array to Hold all the Old y values

	float newX;															// holds the new X value

	float newY;															// holds the new Y value

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

	UPROPERTY(EditDefaultsOnly, Category = "Time Pickup")
		TSubclassOf<AMyTimePickup> timePickup;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
