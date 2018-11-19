// Copyright 1998-2018 Epic Games, Inc. All Rights Reserved.

#include "LearnToDriveGameMode.h"
#include "LearnToDrivePawn.h"
#include "LearnToDriveHud.h"

ALearnToDriveGameMode::ALearnToDriveGameMode()
{
	DefaultPawnClass = ALearnToDrivePawn::StaticClass();
	HUDClass = ALearnToDriveHud::StaticClass();
}
