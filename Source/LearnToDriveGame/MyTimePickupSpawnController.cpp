// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTimePickupSpawnController.h"


// Sets default values
AMyTimePickupSpawnController::AMyTimePickupSpawnController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	// -- Value Sets -- //
	newX = 0.f;
	newY = 0.f;

	// -- Array Set-up -- //
	oldX.SetNum(40);
	oldY.SetNum(40);
}

// Called when the game starts or when spawned
void AMyTimePickupSpawnController::BeginPlay()
{
	Super::BeginPlay();
	
	// driver function, this will run i times on begin play.
	// starts at 0 and moves to 14 
	for (int32 i = 0; i < 40; i++)
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
			newVec.Set(newX, newY, 50.f);							// set the location to the newX, newY, and 145.f units above the ground

			AActor* newActor = GetWorld()->SpawnActor<AMyTimePickup>(timePickup, newVec, FRotator::ZeroRotator, spawnParams);

		}
	}
}

// Called every frame
void AMyTimePickupSpawnController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

float AMyTimePickupSpawnController::generateX(float oldUsedX)
{
	float passBack = 0.f;																	// init a variable to the origin

	passBack = FMath::RandRange(-26500.f, 27000.f);												// generate a number between -26500 and 27000 unreal units

	passBack = passBack + oldUsedX;															// set that number to itself plus the old number 

	if (passBack <  -26500.f || passBack > 27000.f)											// if the number is less that -26500 or greater than 27000 
	{																						// send a recursive call to create a new one 
		passBack = generateX(oldUsedX);
	}

	if (!isUsed(oldX, passBack))															// if the number was used at all, make a recursive call to 
	{																						// generate a new one for use to use 
		passBack = generateX(oldUsedX);
	}

	return passBack;
}

float AMyTimePickupSpawnController::generateY(float oldUsedY)
{
	float passBack = 0.f;																	// init a variable to the origin 
	int maxTry = 0;

	if (maxTry >= 50) {
		return passBack;
	}

	passBack = FMath::RandRange(-3000.f, 3100.f);												// Random number between -3000 & 3100

	passBack = passBack + oldUsedY;															// Add the previous number to the new number

	if (passBack < -3000.f || passBack > 3100.f)											// If that number is less than -3000 or greater than 3100
	{																						// Try and generate a new number and pass it back 
		maxTry++;
		passBack = generateY(oldUsedY);
	}

	if (!isUsed(oldY, passBack))															// Check if oldY has been used before 
	{																						// Try and generate a new Y 
		maxTry++;
		passBack = generateY(oldUsedY);
	}

	return passBack;
}

bool AMyTimePickupSpawnController::isUsed(TArray<float>& oldArray, float numCheck)
{
	bool flag = true;															// Create a flag and set it to it being valid and not used

	for (int32 i = 0; i < oldArray.Num(); i++)									// create a for loop to process the array and cycle through each slot
	{
		if (distanceBetween(oldArray[i], numCheck) < 25.f)						// if the array's slot number and the newly generated number are less 
		{																		// than 50 units apart trip the flag to false
			flag = false;
		}
	}

	return flag;
}

float AMyTimePickupSpawnController::distanceBetween(float inOne, float inTwo)
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

bool AMyTimePickupSpawnController::isOneGreater(float inOne, float inTwo)
{
	bool flag = true;															// assume the first number is greater 

	if (inOne <= inTwo)															// if the first number is less than or equal to the second
	{
		flag = false;															// trip the flag to false
	}

	return flag;
}