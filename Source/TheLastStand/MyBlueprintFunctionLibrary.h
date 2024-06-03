// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Item.h"
#include "Kismet/BlueprintFunctionLibrary.h"
#include "MyBlueprintFunctionLibrary.generated.h"

/**
 * 
 */
UCLASS()
class THELASTSTAND_API UMyBlueprintFunctionLibrary : public UBlueprintFunctionLibrary
{
	GENERATED_BODY()
	
public:
	UFUNCTION(BlueprintCallable)
	static FItem itemInit(int id, int count = 0);

	UFUNCTION(BlueprintCallable)
	static FString getItemName(int id);

	//0: mat 1: use 2:building
	UFUNCTION(BlueprintCallable)
	static int getItemType(int id);

	UFUNCTION(BlueprintCallable)
	static UTexture2D* loadTexture(const FString& path);

};
