// Fill out your copyright notice in the Description page of Project Settings.


#include "MyBlueprintFunctionLibrary.h"

FItem UMyBlueprintFunctionLibrary::itemInit(int id, int count)
{
	FItem cur;
	cur.id = id;
	cur.name = getItemName(id);
	cur.count = count;
	cur.type = getItemType(id);
	cur.url = "/Script/Engine.Texture2D'/Game/Mat/Items/" + FString::FromInt(id) + "." + FString::FromInt(id) + "'";

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
	//else if (id == 7)
	//{
	//	return "Iron pickaxe";
	//}
	else if (id == 8)
	{
		return "Mineral";
	}
	else if (id == 9)
	{
		return "Iron";
	}
	//else if (id == 10)
	//{
	//	return "Hand gun";
	//}
	else if (id == 11)
	{
		return "Drone";
	}
	else if (id == 12)
	{
		return "Cloth";
	}
	else if (id == 13)
	{
		return "Electric Web";
	}
	else if (id == 14)
	{
		return "Rock machine";
	}
	else if (id == 15)
	{
		return "Auto-Rock machine";
	}
	else if (id == 16)
	{
		return "Fire rock";
	}
	else if (id == 17)
	{
		return "Big rock";
	}
	else if (id == 18)
	{
		return "Bullet";
	}
	else if (id == 19)
	{
		return "Granade";
	}
	else if (id == 20)
	{
		return "NAPALM";
	}
	else if (id == 21)
	{
		return "Wall";
	}
	else if (id == 22)
	{
		return "Barb";
	}
	else if (id == 23)
	{
		return "Water";
	}

	return "unknowed item";
}

int UMyBlueprintFunctionLibrary::getItemType(int id)
{
	if (id == 0)return 0;
	if (id == 1)return 0;
	if (id == 2)return 0;
	if (id == 3)return 0;
	if (id == 4)return 0;
	if (id == 5)return 0;
	if (id == 6)return 0;
	if (id == 7)return 0;
	if (id == 8)return 0;
	if (id == 9)return 0;
	if (id == 10)return 0;
	if (id == 11)return 1;
	if (id == 12)return 0;
	if (id == 23)return 0;
	if (id == 13)return 2;
	if (id == 14)return 2;
	if (id == 15)return 2;
	if (id == 16)return 0;
	if (id == 17)return 0;
	if (id == 18)return 0;
	if (id == 19)return 1;
	if (id == 20)return 1;
	if (id == 21)return 2;
	if (id == 22)return 2;

	return -1;
}

UTexture2D* UMyBlueprintFunctionLibrary::loadTexture(const FString& path)
{
	return Cast<UTexture2D>(StaticLoadObject(UTexture2D::StaticClass(), NULL, *path));;
}