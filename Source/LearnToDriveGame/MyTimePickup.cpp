// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTimePickup.h"
#include "Components/SphereComponent.h"
#include "DrawDebugHelpers.h"

// Sets default values
AMyTimePickup::AMyTimePickup()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	sphereRadius = 100.0f;

	collisionSphere = CreateDefaultSubobject<USphereComponent>(TEXT("My Sphere Component"));
	collisionSphere->InitSphereRadius(sphereRadius);
	collisionSphere->SetCollisionProfileName("Trigger");
	RootComponent = collisionSphere;

	myMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("My Mesh"));
	myMesh->SetupAttachment(RootComponent);

	collisionSphere->OnComponentBeginOverlap.AddDynamic(this, &AMyTimePickup::OnOverlapBegin);
}

// Called when the game starts or when spawned
void AMyTimePickup::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void AMyTimePickup::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	//DrawDebugSphere(GetWorld(), GetActorLocation(), sphereRadius, 20, FColor::Purple, false, -1, 0, 1);
}

void AMyTimePickup::OnOverlapBegin(class UPrimitiveComponent* OverlappedComp, class AActor* OtherActor, class UPrimitiveComponent* OtherComp, int32 OtherBodyIndex, bool bFromSweep, const FHitResult& SweepResult)
{
	if ((OtherActor != nullptr) && (OtherActor != this) && (OtherActor == carPawn))
	{
		//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Overlap")));
		Cast<AMyCarPawn>(OtherActor)->AddTime();

		if (carPawn != NULL)
		{
			if (carPawn->GetWorldTimerManager().IsTimerActive(carPawn->GameTimerHandle))
			{
				carPawn->AddTime();
			}
		}
		Destroy();
	}
}

