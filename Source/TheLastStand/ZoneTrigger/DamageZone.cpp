// Fill out your copyright notice in the Description page of Project Settings.


#include "DamageZone.h"

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
	//Cast<AMonster>(cur)->curHP -= dmg;

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