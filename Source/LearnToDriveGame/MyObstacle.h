// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyObstacle.generated.h"

UCLASS()
class LEARNTODRIVEGAME_API AMyObstacle : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* triggerCapsule;

	UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* obstMesh;


public:	
	// Sets default values for this actor's properties
	AMyObstacle();


protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
