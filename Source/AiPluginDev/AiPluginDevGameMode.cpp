// Copyright Epic Games, Inc. All Rights Reserved.

#include "AiPluginDevGameMode.h"
#include "AiPluginDevCharacter.h"
#include "UObject/ConstructorHelpers.h"

AAiPluginDevGameMode::AAiPluginDevGameMode()
{
	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/ThirdPerson/Blueprints/BP_ThirdPersonCharacter"));
	if (PlayerPawnBPClass.Class != NULL)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}
}
