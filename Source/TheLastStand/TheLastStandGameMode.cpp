// Copyright Epic Games, Inc. All Rights Reserved.

#include "TheLastStandGameMode.h"
#include "TheLastStandPlayerController.h"
#include "TheLastStandCharacter.h"
#include "MyPlayerState.h"
#include "UObject/ConstructorHelpers.h"

ATheLastStandGameMode::ATheLastStandGameMode()
{
	// use our custom PlayerController class
	PlayerControllerClass = ATheLastStandPlayerController::StaticClass();
	PlayerStateClass = AMyPlayerState::StaticClass();

	// set default pawn class to our Blueprinted character
	static ConstructorHelpers::FClassFinder<APawn> PlayerPawnBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownCharacter"));
	if (PlayerPawnBPClass.Class != nullptr)
	{
		DefaultPawnClass = PlayerPawnBPClass.Class;
	}

	// set default controller to our Blueprinted controller
	static ConstructorHelpers::FClassFinder<APlayerController> PlayerControllerBPClass(TEXT("/Game/TopDown/Blueprints/BP_TopDownPlayerController"));
	if(PlayerControllerBPClass.Class != NULL)
	{
		PlayerControllerClass = PlayerControllerBPClass.Class;
	}
}