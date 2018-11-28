// Fill out your copyright notice in the Description page of Project Settings.

#include "MyObstacleSpawnController.h"


// Sets default values
AMyObstacleSpawnController::AMyObstacleSpawnController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// -- Value Sets -- //
	newX = 0.f;
	newY = 0.f;

	// -- Array Set-up -- //
	oldX.SetNum(100);
	oldY.SetNum(100);

}

// Called when the game starts or when spawned
void AMyObstacleSpawnController::BeginPlay()
{
	Super::BeginPlay();
	
	// driver function, this will run 100 times on begin play.
	// starts at 0 and moves to 99 
	for (int32 i = 0; i < 100; i++)
	{
		// generate a x for us to use 
		newX = generateX(newX);

		// generate a y for use to use
		newY = generateY(newY);

		// Add the X to the array at the ith slot
		oldX[i] = newX;

		// add the Y to the array at the i slot
		oldY[i] = newY;

		// check if the world exits
		const UWorld* world = GetWorld();

		// if the world does exist 
		if (world)
		{
			// create spawn params
			FActorSpawnParameters spawnParams;
			spawnParams.Owner = this;								// Who spawned this object
			spawnParams.Instigator = Instigator;					// Who Can do damage to this object

			// Create a vector based on our code
			FVector newVec;											// Create a new Vector for us to use
			newVec.Set(newX, newY, 112.f);							// set the location to the newX, newY, and 145.f units above the ground

			AActor* newActor = GetWorld()->SpawnActor<AMyObstacle>(obstacle, newVec, FRotator::ZeroRotator, spawnParams);
			
		}
	}

}

// Called every frame
void AMyObstacleSpawnController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AMyObstacleSpawnController::generateX(float oldUsedX)
{
	float passBack = 0.f;																	// init a variable to the origin

	passBack = FMath::RandRange(-5000, 5000);												// generate a number between -26500 and 27000 unreal units

	passBack = passBack + oldUsedX;															// set that number to itself plus the old number 

	if (passBack <  -5000.f || passBack > 5000.f)											// if the number is less that -26500 or greater than 27000 
	{																						// send a recursive call to create a new one 
		passBack = generateX(oldUsedX);
	}

	if (!isUsed(oldX, passBack))															// if the number was used at all, make a recursive call to 
	{																						// generate a new one for use to use 
		passBack = generateX(oldUsedX);
	}

	return passBack;
}

float AMyObstacleSpawnController::generateY(float oldUsedY)
{
	float passBack = 0.f;																	// init a variable to the origin 

	passBack = FMath::RandRange(-5000, 5000);												// Random number between -3000 & 3100

	passBack = passBack + oldUsedY;															// Add the previous number to the new number

	if (passBack < -5000.f || passBack > 5000.f)											// If that number is less than -3000 or greater than 3100
	{																						// Try and generate a new number and pass it back 
		passBack = generateY(oldUsedY);
	}

	if (!isUsed(oldY, passBack))															// Check if oldY has been used before 
	{																						// Try and generate a new Y 
		passBack = generateY(oldUsedY);
	}

	return passBack;
}

bool AMyObstacleSpawnController::isUsed(TArray<float>& oldArray, float numCheck)
{
	bool flag = true;															// Create a flag and set it to it being valid and not used

	for (int32 i = 0; i < oldArray.Num(); i++)									// create a for loop to process the array and cycle through each slot
	{
		if (distanceBetween(oldArray[i], numCheck) < 50.f)						// if the array's slot number and the newly generated number are less 
		{																		// than 50 units apart trip the flag to false
			flag = false;
		}
	}

	return flag;
}

float AMyObstacleSpawnController::distanceBetween(float inOne, float inTwo)
{
	float passBack = 0.f;														// init a variable to the origin 

	bool flag = isOneGreater(inOne, inTwo);										// check which number is greater and catch the result 

	if (flag == true)															// if the result was true, that the first number is greater
	{
		passBack = inOne - inTwo;												// set the distance between to the first number minus the second
	}
	else                                                                        // if the result was false, that the first number was smaller 
	{
		passBack = inTwo - inOne;                                               // set the distance between to the second number minus the first 
	}

	return passBack;
}

bool AMyObstacleSpawnController::isOneGreater(float inOne, float inTwo)
{
	bool flag = true;															// assume the first number is greater 

	if (inOne <= inTwo)															// if the first number is less than or equal to the second
	{
		flag = false;															// trip the flag to false
	}

	return flag;
}