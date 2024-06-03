// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageZone.h"
#include "../MyEnemy.h"

// Sets default values
ADamageZone::ADamageZone()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void ADamageZone::BeginPlay()
{
	Super::BeginPlay();
	
}

// Called every frame
void ADamageZone::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	for (int i = 0; i < objectList.Num(); i += 1)
	{
		cdList[i] -= DeltaTime;

		if (cdList[i] <= 0) 
		{
			cdList[i] = cd;
			applyDMG(objectList[i]);
		}
	}

	if (curHP <= 0 || curTime <= 0)
	{
		Destroy();
	}

	curTime -= DeltaTime;
}

void ADamageZone::objectEnter(AActor* cur)
{
	objectList.Add(cur);
	cdList.Add(cd);

	applyDMG(cur);
}

void ADamageZone::objectExit(AActor* cur) 
{
	for (int i = 0; i < objectList.Num(); i += 1)
	{
		if (objectList[i] == cur)
		{
			objectList.RemoveAt(i);
			cdList.RemoveAt(i);

			return;
		}
	}
}

void ADamageZone::applyDMG(AActor* cur)
{
	//APPLY DAMAGE TO ACTOR
	Cast<AMyEnemy>(cur)->curHP -= dmg;

	UE_LOG(LogTemp, Warning, TEXT("IS IN"));

	curHP -= 1;
}

void ADamageZone::setProperty(float maxHP, float time, float damage, float cooldown)
{
	curHP = maxHP;
	curTime = time;
	dmg = damage;
	cd = cooldown;
}

AActor* ADamageZone::getClosestEnemy(int index)
{
	if (index >= warningArea.Num())
	{
		index = warningArea.Num() - 1;
	}

	TArray<float> disList;
	TArray<int> indexList;

	for (int i = 0; i < warningArea.Num(); i += 1) 
	{
		disList.Add(FVector::Dist(GetActorLocation(), warningArea[i]->GetActorLocation()));
		indexList.Add(i);
	}

	for (int i = 0; i <= index; i += 1) 
	{
		int curMin = 9999999;
		int curIndex = -1;

		for (int j = 0; j < disList.Num(); j += 1)
		{
			if (disList[j] < curMin)
			{
				curMin = disList[j];
				curIndex = j;
			}
		}

		if (i == index) 
		{
			return warningArea[indexList[curIndex]];
		}

		disList.RemoveAt(curIndex);
		indexList.RemoveAt(curIndex);
	}

	return NULL;
}