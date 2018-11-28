// Fill out your copyright notice in the Description page of Project Settings.

#include "MyObstacle.h"
#include "Components/StaticMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"

// Sets default values
AMyObstacle::AMyObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	////Collision Capsule
	//triggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	//triggerCapsule->InitCapsuleSize(55.f, 96.0f);
	//triggerCapsule->SetCollisionProfileName("Trigger");
	//RootComponent = triggerCapsule;

	////Obstacle Mesh
	//obstMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	//obstMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyObstacle::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

