// Fill out your copyright notice in the Description page of Project Settings.


#include "DestroyableObject.h"
#include "Math/UnrealMathUtility.h"
#include "MyBlueprintFunctionLibrary.h"

// Sets default values
ADestroyableObject::ADestroyableObject()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADestroyableObject::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADestroyableObject::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

void ADestroyableObject::addDropItem(int id, int minCount, int maxCount)
{
	dropItems.Add(UMyBlueprintFunctionLibrary::itemInit(id, FMath::RandRange(minCount, maxCount)));
}

void ADestroyableObject::dropNow(AMyPlayerState* player)
{
	player->receiveItems(dropItems);

	Destroy();
}