// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Item.h"
#include "MyPlayerState.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class THELASTSTAND_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
private:
	AActor* playerBuildPreset;
	int curBuildingType;

public:
	int itemTypeCount = 24;
	TArray<TArray<FItem>> synthesisList;

	void initSynthesisList();

	void playerUseItem(AMyPlayerState* playState, int type, FVector startPos, FVector endPos);
	void playerTryBuild(AMyPlayerState* playState, int type, FVector pos);
	void playerStopBuild(AMyPlayerState* playState);

	void setBuidingPresetPos(FVector pos);
	void setBuildingPresetRot(bool isUp, float deg);
	bool playerStartBuild(AMyPlayerState* playState);

	void shootAtPos(AMyPlayerState* playState, FVector pos);
};
