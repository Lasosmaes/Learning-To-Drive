// Fill out your copyright notice in the Description page of Project Settings.

#include "MyCarPawn.h"
#include "MyCarWheelFront.h"
#include "MyCarWheelRear.h"
#include "Components/SkeletalMeshComponent.h"
#include "Components/CapsuleComponent.h"
#include "GameFramework/SpringArmComponent.h"
#include "Camera/CameraComponent.h"
#include "Components/InputComponent.h"
#include "WheeledVehicleMovementComponent4W.h"
#include "Engine/SkeletalMesh.h"
#include "Engine/Engine.h"
#include "TimerManager.h"
#include "UObject/ConstructorHelpers.h"
#include "Components/TextRenderComponent.h"
#include "Materials/Material.h"
#include "GameFramework/Controller.h"

#define LOCTEXT_NAMESPACE "VehiclePawn"

AMyCarPawn::AMyCarPawn()
{
	// Car mesh
	static ConstructorHelpers::FObjectFinder<USkeletalMesh> CarMesh(TEXT("/Game/Vehicle/Sedan/Sedan_SkelMesh.Sedan_SkelMesh"));
	GetMesh()->SetSkeletalMesh(CarMesh.Object);

	static ConstructorHelpers::FClassFinder<UObject> AnimBPClass(TEXT("/Game/Vehicle/Sedan/Sedan_AnimBP"));
	GetMesh()->SetAnimInstanceClass(AnimBPClass.Class);

	/*triggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	triggerCapsule->InitCapsuleSize(55.f, 96.0f);;
	triggerCapsule->SetCollisionProfileName(TEXT("Trigger"));*/

	// Simulation
	UWheeledVehicleMovementComponent4W* Vehicle4W = CastChecked<UWheeledVehicleMovementComponent4W>(GetVehicleMovement());

	check(Vehicle4W->WheelSetups.Num() == 4);

	Vehicle4W->WheelSetups[0].WheelClass = UMyCarWheelFront::StaticClass();
	Vehicle4W->WheelSetups[0].BoneName = FName("Wheel_Front_Left");
	Vehicle4W->WheelSetups[0].AdditionalOffset = FVector(0.f, -12.f, 0.f);

	Vehicle4W->WheelSetups[1].WheelClass = UMyCarWheelFront::StaticClass();
	Vehicle4W->WheelSetups[1].BoneName = FName("Wheel_Front_Right");
	Vehicle4W->WheelSetups[1].AdditionalOffset = FVector(0.f, 12.f, 0.f);

	Vehicle4W->WheelSetups[2].WheelClass = UMyCarWheelRear::StaticClass();
	Vehicle4W->WheelSetups[2].BoneName = FName("Wheel_Rear_Left");
	Vehicle4W->WheelSetups[2].AdditionalOffset = FVector(0.f, -12.f, 0.f);

	Vehicle4W->WheelSetups[3].WheelClass = UMyCarWheelRear::StaticClass();
	Vehicle4W->WheelSetups[3].BoneName = FName("Wheel_Rear_Right");
	Vehicle4W->WheelSetups[3].AdditionalOffset = FVector(0.f, 12.f, 0.f);

	// Create a spring arm component
	SpringArm = CreateDefaultSubobject<USpringArmComponent>(TEXT("SpringArm0"));
	SpringArm->TargetOffset = FVector(0.f, 0.f, 200.f);
	SpringArm->SetRelativeRotation(FRotator(-15.f, 0.f, 0.f));
	SpringArm->SetupAttachment(RootComponent);
	SpringArm->TargetArmLength = 600.0f;
	SpringArm->bEnableCameraRotationLag = true;
	SpringArm->CameraRotationLagSpeed = 7.f;
	SpringArm->bInheritPitch = false;
	SpringArm->bInheritRoll = false;

	// Create camera component 
	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera0"));
	Camera->SetupAttachment(SpringArm, USpringArmComponent::SocketName);
	Camera->bUsePawnControlRotation = false;
	Camera->FieldOfView = 90.f;

	/*triggerCapsule->OnComponentBeginOverlap.AddDynamic(this, &AMyCarPawn::OnOverlapBegin);*/

	bInReverseGear = false;
}

void AMyCarPawn::SetupPlayerInputComponent(UInputComponent * InputComponent)
{
	Super::SetupPlayerInputComponent(InputComponent);

	// set up gameplay key bindings
	check(InputComponent);

	InputComponent->BindAxis("MoveForward", this, &AMyCarPawn::MoveForward);
	InputComponent->BindAxis("MoveRight", this, &AMyCarPawn::MoveRight);

	InputComponent->BindAction("Handbrake", IE_Pressed, this, &AMyCarPawn::OnHandbrakePressed);
	InputComponent->BindAction("Handbrake", IE_Released, this, &AMyCarPawn::OnHandbrakeReleased);
}

void AMyCarPawn::Tick(float Delta)
{
	Super::Tick(Delta);

	// Setup the flag to say we are in reverse gear
	bInReverseGear = GetVehicleMovement()->GetCurrentGear() < 0;

	// Update the strings used in the HUD
	UpdateHUDStrings();

	currentTime = GetWorld()->GetTimerManager().GetTimerRemaining(GameTimerHandle);	//Check current time
	/*if (currentTime >= 0.0f) 
	{
		if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Time left: %f"), currentTime));
	}*/
}

void AMyCarPawn::BeginPlay()
{
	Super::BeginPlay();

	isPlayerDead = false;
	timeReduction = 5.0f;
	timeAddition = 5.0f;

	//Player 'life' timer
	GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AMyCarPawn::PlayerDeath, startTime, false);
	BeginTutUI();
}

void AMyCarPawn::MoveForward(float Val)
{
	GetVehicleMovementComponent()->SetThrottleInput(Val);
}

void AMyCarPawn::MoveRight(float Val)
{
	GetVehicleMovementComponent()->SetSteeringInput(Val);
}

void AMyCarPawn::OnHandbrakePressed()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(true);
}

void AMyCarPawn::OnHandbrakeReleased()
{
	GetVehicleMovementComponent()->SetHandbrakeInput(false);
}

void AMyCarPawn::UpdateHUDStrings()
{
	float KPH = FMath::Abs(GetVehicleMovement()->GetForwardSpeed()) * 0.036f;
	int32 KPH_int = FMath::FloorToInt(KPH);

	int32 TimeRemaining = FMath::FloorToInt(currentTime);

	// Using FText because this is display text that should be localizable
	SpeedDisplayString = FText::Format(LOCTEXT("SpeedFormat", "{0} km/h"), FText::AsNumber(KPH_int));

	TimerDisplayString = FText::Format(LOCTEXT("Time Remaining", "{0} s"), FText::AsNumber(TimeRemaining));

	if (bInReverseGear == true)
	{
		GearDisplayString = FText(LOCTEXT("ReverseGear", "R"));
	}
	else
	{
		int32 Gear = GetVehicleMovement()->GetCurrentGear();
		GearDisplayString = (Gear == 0) ? LOCTEXT("N", "N") : FText::AsNumber(Gear);
	}
}

void AMyCarPawn::PlayerDeath()
{
	//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Time ran out: Player died")));

	AController* controller = GetController();

	if (controller != NULL) 
	{
		controller->UnPossess();	//'Kill' player
	}

	GetWorldTimerManager().ClearTimer(GameTimerHandle);

	isPlayerDead = true;	//Player has died
	PlayerDied();	//Show failure widget
}

void AMyCarPawn::PlayerWin()
{
	AController* controller = GetController();

	if (controller != NULL)
	{
		controller->UnPossess();	//'Kill' player
	}

	GetWorldTimerManager().ClearTimer(GameTimerHandle);
	PlayerCompleted();
}

void AMyCarPawn::ReduceTime()
{
	if (GetWorldTimerManager().GetTimerRemaining(GameTimerHandle) >= timeReduction)												//If remaining time >= time to be reduced, then reduce time
	{
		GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AMyCarPawn::PlayerDeath, currentTime - timeReduction, false);
		TimeIsReduced();
	}																															//If remaining time < time to be reduced, clear timer and kill player
	else
	{
		GetWorldTimerManager().ClearTimer(GameTimerHandle);
		PlayerDeath();
	}
}

void AMyCarPawn::AddTime()
{
	if (GetWorldTimerManager().GetTimerRemaining(GameTimerHandle) >= timeReduction)												//If remaining time >= time to be reduced, then reduce time
	{
		GetWorldTimerManager().SetTimer(GameTimerHandle, this, &AMyCarPawn::PlayerDeath, currentTime + timeAddition, false);
	}
}

//void AMyCarPawn::OnOverlapBegin(UPrimitiveComponent * OverlappedComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult & SweepResult)
//{
//	if (OtherActor && (OtherActor != this) && OtherComp)
//	{
//		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, TEXT("Overlap Begin"));
//	}
//}

void AMyCarPawn::TimeIsReduced_Implementation()
{
}

void AMyCarPawn::PlayerDied_Implementation()
{
}

void AMyCarPawn::PlayerCompleted_Implementation()
{
}

void AMyCarPawn::BeginTutUI_Implementation()
{
}

#undef LOCTEXT_NAMESPACE