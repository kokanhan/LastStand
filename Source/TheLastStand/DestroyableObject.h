// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "Item.h"
#include "MyPlayerState.h"
#include "DestroyableObject.generated.h"

UCLASS()
class THELASTSTAND_API ADestroyableObject : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	ADestroyableObject();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

public:
	TArray<FItem> dropItems;

	UFUNCTION(BlueprintCallable)
	void addDropItem(int id, int minCount, int maxCount);

	void dropNow(AMyPlayerState* player);
};
