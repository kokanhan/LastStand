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
	TArray<FItem> items;

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
};
