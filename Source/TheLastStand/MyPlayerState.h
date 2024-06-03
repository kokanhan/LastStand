// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/PlayerState.h"
#include "Item.h"
#include "MyUserWidget.h"
#include "MyPlayerState.generated.h"

/**
 * 
 */
UCLASS()
class THELASTSTAND_API AMyPlayerState : public APlayerState
{
	GENERATED_BODY()
	
public: 
	UPROPERTY(BlueprintReadWrite)
	TArray<FItem> items;

	UPROPERTY(BlueprintReadWrite)
	TArray<FItem> equippedItems;

	UPROPERTY(BlueprintReadWrite)
	UMyUserWidget* layout;

public:
	void initItemList();

	UFUNCTION(BlueprintCallable)
	int getSynListCount();

	UFUNCTION(BlueprintCallable)
	TArray<FItem> getSynthesisItemReceipt(int id);

	UFUNCTION(BlueprintCallable)
	bool synthesisItem(int id);

	UFUNCTION(BlueprintCallable)
	void printItem();

	UPROPERTY(BlueprintReadOnly)
	TArray<AActor*> collectableObjects;

	void receiveItems(TArray<FItem> dropItems);

	UFUNCTION(BlueprintCallable)
	int getEquippedItemLength();
	UFUNCTION(BlueprintCallable)
	void equipItem(int slotIndex, int itemID);
	UFUNCTION(BlueprintCallable)
	void unequipItem(int slotIndex);
};
