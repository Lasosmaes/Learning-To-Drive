// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/TriggerBox.h"
#include "MyCarPawn.h"
#include "MyFinishArea.generated.h"

/**
 * 
 */
UCLASS()
class LEARNTODRIVEGAME_API AMyFinishArea : public ATriggerBox
{
	GENERATED_BODY()

	//// create trigger capsule
	//UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
	//	class UCapsuleComponent* triggerCapsule;

	AMyCarPawn* carPawn;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// constructor sets default values for this actor's properties
	AMyFinishArea();

	// overlap begin function
	UFUNCTION()
		void OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor);

	
	
};
