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
	void showSynListLayout();

	UFUNCTION(BlueprintImplementableEvent)
	void hideSynListLayout();

	UFUNCTION(BlueprintImplementableEvent)
	void drawSlotsInSynItem(const TArray<FVector>& pos);

	UFUNCTION(BlueprintImplementableEvent)
	void showInventoryLayout(bool isShow);
};
