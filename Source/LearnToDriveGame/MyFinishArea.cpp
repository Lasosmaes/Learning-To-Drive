// Fill out your copyright notice in the Description page of Project Settings.

#include "MyFinishArea.h"
#include "DrawDebugHelpers.h"

AMyFinishArea::AMyFinishArea()
{
	//// declare trigger capsule
	//triggerCapsule = CreateDefaultSubobject<UCapsuleComponent>(TEXT("Trigger Capsule"));
	//triggerCapsule->InitCapsuleSize(55.f, 96.0f);;
	//triggerCapsule->SetCollisionProfileName(TEXT("Trigger"));
	//triggerCapsule->SetupAttachment(triggerCapsule);

	// declare overlap events
	OnActorBeginOverlap.AddDynamic(this, &AMyFinishArea::OnOverlapBegin);

}

// Called when the game starts or when spawned
void AMyFinishArea::BeginPlay()
{
	Super::BeginPlay();

	//DrawDebugBox(GetWorld(), GetActorLocation(), GetActorScale() * 100, FColor::Turquoise, true, -1, 0, 5);
}

void AMyFinishArea::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	
}

void AMyFinishArea::OnOverlapBegin(class AActor* OverlappedActor, class AActor* OtherActor)
{
		if (OtherActor->IsA(AMyCarPawn::StaticClass()))
		{
			Cast<AMyCarPawn>(OtherActor)->PlayerWin();
			//if (GEngine) GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Green, FString::Printf(TEXT("Overlap")));
			if (carPawn != NULL)
			{
				carPawn->PlayerWin();
			}
		}
}