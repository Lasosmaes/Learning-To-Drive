// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/HUD.h"
#include "MyCarPawnHUD.generated.h"

/**
 * 
 */
UCLASS()
class LEARNTODRIVEGAME_API AMyCarPawnHUD : public AHUD
{
	GENERATED_BODY()
	
public:
	AMyCarPawnHUD();

	/** Font used to render the vehicle info */
	UPROPERTY()
		UFont* HUDFont;

	// Begin AHUD interface
	virtual void DrawHUD() override;
	// End AHUD interface
	
	
};
