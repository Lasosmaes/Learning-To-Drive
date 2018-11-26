// Fill out your copyright notice in the Description page of Project Settings.

#include "MyObstacleSpawnController.h"


// Sets default values
AMyObstacleSpawnController::AMyObstacleSpawnController()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyObstacleSpawnController::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyObstacleSpawnController::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyObstacleSpawnController::SpawnObstacle()
{

}

