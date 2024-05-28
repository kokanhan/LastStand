// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/GameStateBase.h"
#include "Item.h"
#include "MyGameStateBase.generated.h"

/**
 * 
 */
UCLASS()
class THELASTSTAND_API AMyGameStateBase : public AGameStateBase
{
	GENERATED_BODY()
	
public:
	int itemTypeCount = 22;
	TArray<TArray<FItem>> synthesisList;

	void initSynthesisList();
};