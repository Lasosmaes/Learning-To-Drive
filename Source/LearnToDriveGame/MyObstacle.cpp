// Fill out your copyright notice in the Description page of Project Settings.

#include "MyObstacle.h"
#include "Components/CapsuleComponent.h"
#include "UObject/ConstructorHelpers.h"
#include "Kismet/KismetMathLibrary.h"
#include "TimerManager.h"



// Sets default values
AMyObstacle::AMyObstacle()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	//Collision Capsule
	capsuleCollider = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Capsule Component"));
	capsuleCollider->InitCapsuleSize(55.f, 96.0f);
	capsuleCollider->SetNotifyRigidBodyCollision(true);
	capsuleCollider->BodyInstance.SetCollisionProfileName("BlockAllDynamic");
	capsuleCollider->OnComponentHit.AddDynamic(this, &AMyObstacle::OnCompHit);

	RootComponent = capsuleCollider;

	////Obstacle Mesh
	//obstMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("Static Mesh"));
	//obstMesh->SetupAttachment(RootComponent);
}

// Called when the game starts or when spawned
void AMyObstacle::BeginPlay()
{
	Super::BeginPlay();
	
	canLoseTime = true;
	
}

// Called every frame
void AMyObstacle::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void AMyObstacle::OnCompHit(UPrimitiveComponent * HitComp, AActor * OtherActor, UPrimitiveComponent * OtherComp, FVector NormalImpulse, const FHitResult & Hit)
{
	if (canLoseTime) {
		if ((OtherActor != NULL) && (OtherActor != this) && (OtherComp != NULL))
		{
			if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("I Hit: %s"), *OtherActor->GetName()));
			canLoseTime = false;
			GetWorldTimerManager().SetTimer(CooldownTimerHandle,this, &AMyObstacle::ResetCooldown, 2.0f, false);
		}
	}
}

void AMyObstacle::ResetCooldown()
{
	canLoseTime = true;
}
