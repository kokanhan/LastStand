// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Item.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class THELASTSTAND_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public: 
	TArray<FItem> items;
};
