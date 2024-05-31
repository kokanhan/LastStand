// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Blueprint/UserWidget.h"
#include "MyUserWidget.generated.h"

/**
 * 
 */
UCLASS()
class THELASTSTAND_API UMyUserWidget : public UUserWidget
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintImplementableEvent)
	void showLayout(bool isShow);

	UFUNCTION(BlueprintImplementableEvent)
	void showSynListLayout(bool isShow);

	UFUNCTION(BlueprintImplementableEvent)
	void showInventoryLayout(bool isShow);

	UFUNCTION(BlueprintImplementableEvent)
	void showPlayerStatusLayout(bool isShow);

	UFUNCTION(BlueprintImplementableEvent)
	void drawSlotsInSynItem(const TArray<FVector>& pos);

	UFUNCTION(BlueprintImplementableEvent)
	void showHintLayout(bool isShow);

	UFUNCTION(BlueprintImplementableEvent)
	void pumpHintText(const FVector& screenPos, const FString& text);
};
