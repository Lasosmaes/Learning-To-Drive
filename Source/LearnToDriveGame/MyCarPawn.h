// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "WheeledVehicle.h"
#include "MyCarPawn.generated.h"

class UCameraComponent;
class USpringArmComponent;
class UInputComponent;

UCLASS()
class LEARNTODRIVEGAME_API AMyCarPawn : public AWheeledVehicle
{
	GENERATED_BODY()

	/*UPROPERTY(VisibleAnywhere, Category = "Trigger Capsule")
		class UCapsuleComponent* triggerCapsule;*/

	/** Spring arm that will offset the camera */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		USpringArmComponent* SpringArm;

	/** Camera component that will be our viewpoint */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly, meta = (AllowPrivateAccess = "true"))
		UCameraComponent* Camera;

public:
	AMyCarPawn();

	//HUD
	/** The current speed as a string e.g. 10 km/h */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
		FText SpeedDisplayString;
	/** The current gear as a string (R,N, 1,2 etc) */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
		FText GearDisplayString;
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
		/** The color of the in-car gear text in forward gears */
		FColor	GearDisplayColor;
	/** The current time remaining as a string e.g. 10s */
	UPROPERTY(Category = Display, VisibleDefaultsOnly, BlueprintReadOnly)
		FText TimerDisplayString;

	/** Are we in reverse gear */
	UPROPERTY(Category = Camera, VisibleDefaultsOnly, BlueprintReadOnly)
		bool bInReverseGear;

	//Check if player died
	bool isPlayerDead;

	//Handle to manage timer
	FTimerHandle GameTimerHandle;

	//Controller
	AController* controller;

	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float startTime;

	//Current player 'life' time remaining
	UPROPERTY(Category = Gameplay, VisibleAnywhere, BlueprintReadOnly)
		float currentTime;

	//Time to reduce by when collision occurs
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float timeReduction;
	//Time to reduce by when collision occurs
	UPROPERTY(Category = Gameplay, EditAnywhere, BlueprintReadOnly)
		float timeAddition;

	// Begin Pawn interface
	virtual void SetupPlayerInputComponent(UInputComponent* InputComponent) override;
	// End Pawn interface

	//Blueprint delegate events
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void TimeIsReduced();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void PlayerDied();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void PlayerCompleted();
	UFUNCTION(BlueprintNativeEvent, BlueprintCallable)
		void BeginTutUI();

	// Begin Actor interface
	virtual void Tick(float Delta) override;

protected:
	virtual void BeginPlay() override;

public:
	// End Actor interface

	/** Handle pressing forwards */
	void MoveForward(float Val);
	/** Handle pressing right */
	void MoveRight(float Val);
	/** Handle handbrake pressed */
	void OnHandbrakePressed();
	/** Handle handbrake released */
	void OnHandbrakeReleased();

	//Reduce player 'life' time
	void ReduceTime();
	//Add to player 'life' time
	void AddTime();

	//Player won
	void PlayerWin();

	/*UFUNCTION()
		void OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult);*/

private:
	/** Update the gear and speed strings */
	void UpdateHUDStrings();

	//Kill player
	void PlayerDeath();
	

	/* Are we on a 'slippery' surface */
	bool bIsLowFriction;

public:
	/** Returns SpringArm subobject **/
	FORCEINLINE USpringArmComponent* GetSpringArm() const { return SpringArm; }
	/** Returns Camera subobject **/
	FORCEINLINE UCameraComponent* GetCamera() const { return Camera; }

};
