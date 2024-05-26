// Copyright Epic Games, Inc. All Rights Reserved.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameModeBase.h"
#include "TheLastStandGameMode.generated.h"

UCLASS(minimalapi)
class ATheLastStandGameMode : public AGameModeBase
{
	GENERATED_BODY()

public:
	ATheLastStandGameMode();

public:
	virtual void PostLogin(APlayerController* NewPlayer);
};



