// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCarPawn.h"
#include "MyTimePickup.generated.h"

UCLASS()
class LEARNTODRIVEGAME_API AMyTimePickup : public AActor
{
	GENERATED_BODY()
	
	AMyCarPawn* carPawn;

public:	
	// Sets default values for this actor's properties
	AMyTimePickup();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	UPROPERTY(VisibleAnywhere)
		class USphereComponent* collisionSphere;

	UPROPERTY(VisibleAnywhere)
		class UStaticMeshComponent* myMesh;

	float sphereRadius;

	UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);
	
};
