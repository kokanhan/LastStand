// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

FItem UMyBlueprintFunctionLibrary::itemInit(int id, int count)
{
	FItem cur;
	cur.id = id;
	cur.name = getItemName(id);
	cur.count = count;

	return cur;
}

FString UMyBlueprintFunctionLibrary::getItemName(int id) 
{
	if (id == 0) 
	{
		return "Wood Base";
	}
	else if (id == 1) 
	{
		return "Electric Wire";
	}
	else if (id == 2)
	{
		return "Battery";
	}
	else if (id == 3)
	{
		return "Electric Web";
	}

	return "unknowed item";
}