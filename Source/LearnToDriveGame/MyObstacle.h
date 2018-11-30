// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "MyCarPawn.h"
#include "MyObstacle.generated.h"

UCLASS()
class LEARNTODRIVEGAME_API AMyObstacle : public AActor
{
	GENERATED_BODY()

	UPROPERTY(VisibleAnywhere)
		class UCapsuleComponent* capsuleCollider;

	/*UPROPERTY(Category = Mesh, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		class UStaticMeshComponent* obstMesh;*/

	AMyCarPawn* carPawn;

	//Is collision cooldown active
	bool canLoseTime;

	//Handle to manage timer
	FTimerHandle CooldownTimerHandle;

public:	
	// Sets default values for this actor's properties
	AMyObstacle();

	//Collision detection
	UFUNCTION()
		void OnCompHit(UPrimitiveComponent* HitComp, AActor* OtherActor, UPrimitiveComponent* OtherComp, FVector NormalImpulse, const FHitResult& Hit);

	//Reset collision cooldown
	UFUNCTION()
		void ResetCooldown();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	
};
