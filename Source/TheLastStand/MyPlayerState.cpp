// Fill out your copyright notice in the Description page of Project Settings.


#include "MyPlayerState.h"
#include "MyGameStateBase.h"
#include "MyBlueprintFunctionLibrary.h"

void AMyPlayerState::initItemList() 
{
	TArray<int32> ids = { 0, 1, 2, 3, 4, 5, 6, 8, 9, 11, 12, 13, 14, 15, 18, 19, 20, 21, 22, 23 };


	AMyGameStateBase* gameState = GetWorld()->GetGameState<AMyGameStateBase>();

	for (int i = 0; i < gameState->itemTypeCount; i += 1)
	{
		if (ids.Contains(i))
		{
			items.Add(UMyBlueprintFunctionLibrary::itemInit(i, 3));
		}
		else 
		{
			items.Add(UMyBlueprintFunctionLibrary::itemInit(i, 0));
		}
	}
	
	equippedItems.Add(UMyBlueprintFunctionLibrary::itemInit(-1));
	equippedItems.Add(UMyBlueprintFunctionLibrary::itemInit(-1));
	equippedItems.Add(UMyBlueprintFunctionLibrary::itemInit(-1));
	equippedItems.Add(UMyBlueprintFunctionLibrary::itemInit(-1));
	equippedItems.Add(UMyBlueprintFunctionLibrary::itemInit(-1));
	equippedItems.Add(UMyBlueprintFunctionLibrary::itemInit(-1));

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

	items[list[0].id].count += list[0].count;

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

void AMyPlayerState::receiveItems(TArray<FItem> dropItems)
{
	for (int i = 0; i < dropItems.Num(); i += 1)
	{
		items[dropItems[i].id].count += dropItems[i].count;
	}
}

void AMyPlayerState::equipItem(int slotIndex, int itemID) 
{
	if (slotIndex < 6  && (items[itemID].type == 1 || items[itemID].type == 2))
	{
		equippedItems[slotIndex] = items[itemID];
		layout->setEquipItemURL(slotIndex, items[itemID].url);//
	}
}

void AMyPlayerState::unequipItem(int slotIndex)
{
	equippedItems[slotIndex] = UMyBlueprintFunctionLibrary::itemInit(-1);
}

int AMyPlayerState::getEquippedItemLength()
{
	for (int i = 0; i < 6; i += 1) 
	{
		if (equippedItems[i].id == -1 || items[equippedItems[i].id].count == 0)
		{
			return i;
		}
	}
	
	return 6;
}
