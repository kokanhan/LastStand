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
		return "Wood";
	}
	else if (id == 1) 
	{
		return "Electric wire";
	}
	else if (id == 2)
	{
		return "Battery";
	}
	else if (id == 3)
	{
		return "Rock";
	}
	else if (id == 4)
	{
		return "Oil";
	}
	else if (id == 5)
	{
		return "Zipper";
	}
	else if (id == 6)
	{
		return "Trap wood";
	}
	else if (id == 7)
	{
		return "Iron pickaxe";
	}
	else if (id == 8)
	{
		return "Mineral";
	}
	else if (id == 9)
	{
		return "Iron";
	}
	else if (id == 10)
	{
		return "Hand gun";
	}
	else if (id == 11)
	{
		return "No man flyer";
	}
	else if (id == 12)
	{
		return "Cloth";
	}
	else if (id == 23)
	{
		return "Water";
	}
	else if (id == 13)
	{
		return "Electric Web";
	}
	else if (id == 14)
	{
		return "Throw rock machine";
	}
	else if (id == 15)
	{
		return "Auto throw rock machine";
	}
	else if (id == 16)
	{
		return "Fire rock for rock machine";
	}
	else if (id == 17)
	{
		return "Big rock for rock machine";
	}
	else if (id == 18)
	{
		return "Bullet";
	}
	else if (id == 19)
	{
		return "Bomb";
	}
	else if (id == 20)
	{
		return "Poison bomb";
	}
	else if (id == 21)
	{
		return "Fence";
	}
	else if (id == 22)
	{
		return "Back-Fierce";
	}
	else if (id == 23)
	{
		return "Water";
	}

	return "unknowed item";
}

UTexture2D* UMyBlueprintFunctionLibrary::loadTexture(const FString& path)
{
	return Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *path));;
}