// Fill out your copyright notice in the Description page of Project Settings.


#include "MyGameStateBase.h"
#include "MyBlueprintFunctionLibrary.h"

void AMyGameStateBase::initSynthesisList() 
{
	TArray<FItem> electricWeb;
	electricWeb.Add(UMyBlueprintFunctionLibrary::itemInit(3, 1));
	electricWeb.Add(UMyBlueprintFunctionLibrary::itemInit(0, 2));
	electricWeb.Add(UMyBlueprintFunctionLibrary::itemInit(1, 4));
	electricWeb.Add(UMyBlueprintFunctionLibrary::itemInit(2, 4));
	synthesisList.Add(electricWeb);
}