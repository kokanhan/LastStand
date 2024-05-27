// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "MyGameStateBase.h"
#include "MyBlueprintFunctionLibrary.h"

void AMyPlayerState::initItemList() 
{
	AMyGameStateBase* gameState = GetWorld()->GetGameState<AMyGameStateBase>();

	for (int i = 0; i < gameState->itemTypeCount; i += 1)
	{
		items.Add(UMyBlueprintFunctionLibrary::itemInit(i, 20));
	}
}

int AMyPlayerState::getSynListCount()
{
	return GetWorld()->GetGameState<AMyGameStateBase>()->synthesisList.Num();
}

TArray<FItem> AMyPlayerState::getSynthesisItemReceipt(int id)
{
	return GetWorld()->GetGameState<AMyGameStateBase>()->synthesisList[id];
}

bool AMyPlayerState::synthesisItem(int id)
{
	TArray<FItem> list = getSynthesisItemReceipt(id);

	for (int i = 1; i < list.Num(); i += 1) 
	{
		if (items[list[i].id].count < list[i].count) 
		{
			return false;
		}
	}

	for (int i = 1; i < list.Num(); i += 1)
	{
		items[list[i].id].count -= list[i].count;
	}

	items[list[0].id].count += 1;

	return true;
}

void AMyPlayerState::printItem()
{
	FString s = "";

	for (int i = 0; i < items.Num(); i += 1)
	{
		if (items[i].count > 0) 
		{
			s += items[i].name + " " + FString::FromInt(items[i].count) + "\n";
		}
	}

	UE_LOG(LogTemp, Warning, TEXT("%s"), *s);
}